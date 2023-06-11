/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 other_trials/ssl_extract.cpp -lpcap -lssl -lcrypto -o .bin/other_trials@@ssl_extract.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/other_trials@@ssl_extract.bin
*/

#include <iostream>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <openssl/x509.h>

using namespace std;

const int ETHERNET_HEADER_LEN = 14;

struct SSLPacketHeader {
    uint8_t type;
    uint16_t version;
    uint16_t length;
};

void output_ssl_certificate(BIO* bio) {
  cout << "reach place 5" << endl;
  int bio_length = BIO_ctrl_pending(bio);
  u_char len_buf[3];
  int bytes_read = BIO_read(bio, len_buf, 3);
  int cert_len = len_buf[0]*256*256 + len_buf[1]*256 + len_buf[2];
  u_char cert_buf[cert_len];
  int bytes_read2 = BIO_read(bio, cert_buf, cert_len);
  // cout << "bytes_read: " << bytes_read << "buf: " << buf[0]+0 << ", " << buf[1]+0 << ", " << buf[2]+0 << endl;
  BIO* bio_temp = BIO_new(BIO_s_mem());
  BIO_write(bio_temp, cert_buf, cert_len);
  SSL_CTX* ctx = SSL_CTX_new(SSLv23_server_method());
  SSL* ssl = SSL_new(ctx);
  SSL_set_accept_state(ssl);
  cout << "&&&& bio_temp len: " << BIO_ctrl_pending(bio_temp) << endl;
  SSL_set_bio(ssl, bio_temp, bio_temp);
  cout << "SSL State: " << SSL_state_string_long(ssl) << endl;
  try {
    X509* cert = SSL_get_peer_certificate(ssl);
    if (cert != nullptr) {
      cout << "reach place 5.2" << endl;
      X509_print_fp(stdout, cert); // Print certificate details to stdout
      X509_free(cert);
    }
  } catch (const std::exception& ex) {
    // Catch any exception and print the error message
    std::cerr << "An exception occurred: " << ex.what() << std::endl;
  }
  // X509* cert = PEM_read_bio_X509(bio_temp, nullptr, nullptr, nullptr);
  cout << "reach place 5.1, " << "bio len: " << bio_length << endl;
  if (bio_temp != nullptr) {
    BIO_free(bio_temp);
  }
  // SSL_free(ssl);
  cout << "reach place 5.4" << endl;
  BIO_reset(bio);
}

void processPacket(const u_char* packet, int packetLength, int loop_num, BIO* bio, int & remained_cert_len) {
  const struct ip* ipHeader = (struct ip*)(packet + ETHERNET_HEADER_LEN); // Skip Ethernet header
  if ((int) ipHeader->ip_p != 6) return; // only proceed if the current protocol is TCP

  const struct tcphdr* tcpHeader = (struct tcphdr*)(packet + ETHERNET_HEADER_LEN + ipHeader->ip_hl * 4); // Skip IP header
  int source_port = *(packet + ETHERNET_HEADER_LEN + ipHeader->ip_hl * 4) * 256 + *(packet + ETHERNET_HEADER_LEN + ipHeader->ip_hl * 4 + 1);
  if (source_port != 443) return; // only proceed if the current packet comes from source port 443, to filter SSL packets

  int tcpHeaderLength = tcpHeader->th_off * 4;
  int sslPacketLength = packetLength - ETHERNET_HEADER_LEN - ipHeader->ip_hl * 4 - tcpHeaderLength;
  if (sslPacketLength <= 0) return; // another filter to filter SSL packets

  const u_char* sslPacket;
  sslPacket = packet + ETHERNET_HEADER_LEN + ipHeader->ip_hl * 4 + tcpHeaderLength;

  if (remained_cert_len > 0) {
    cout << "reach place 6. loop_num: " << loop_num << endl;
    int buf_write_len = min(sslPacketLength, remained_cert_len);
    BIO_write(bio, sslPacket, buf_write_len);
    remained_cert_len -= buf_write_len;
    if (remained_cert_len <= 0) output_ssl_certificate(bio);
    return;
  }

  struct SSLPacketHeader* sslHeader = (struct SSLPacketHeader*) sslPacket;

  if (sslHeader->type != 22) return; // only proceed if the type is a handshake type


  int total_ssl_header_len = 5;

  const u_char* handshakeTypePtr = sslPacket + 5;
  int handshakeType = *handshakeTypePtr;

  cout << "reach place 2. loop_num: " << loop_num << ", handshakeType: " << handshakeType << endl;
  int handshakePacLen = *(sslPacket + 3) * 256 + *(sslPacket + 4);
  if (handshakeType == 2) {
    handshakeTypePtr += handshakePacLen;
    if (*handshakeTypePtr + 0 != 22) return;
    handshakeTypePtr += 5;
    handshakeType = *handshakeTypePtr;
    total_ssl_header_len += handshakePacLen;
    cout << "reach place 3. loop_num: " << loop_num << ", handshakeTypePtr: " << *handshakeTypePtr + 0 << endl;
  }
  if (handshakeType == 11) {
    int certPayloadLen = *(handshakeTypePtr + 1) * 256 * 256 + *(handshakeTypePtr + 2) * 256 + *(handshakeTypePtr + 3);
    total_ssl_header_len += 7;
    remained_cert_len = certPayloadLen;
    u_char* certInitPtr = (u_char*) handshakeTypePtr + 7;
    cout << "reach place 4. loop_num: " << loop_num << ", certInitPtr: " << *certInitPtr + 0 << ", certPayloadLen: " << certPayloadLen << endl;
    cout << "--- sslPacketLength: " << sslPacketLength << ", total_ssl_header_len: " << total_ssl_header_len << endl;
    for (int i = 0; i < 10; ++i) {
      cout << *(certInitPtr + i) + 0 << ", ";
    }
    cout << endl;
    int cert_payload_len_in_curr_pac = sslPacketLength - total_ssl_header_len;
    if (cert_payload_len_in_curr_pac > 0) {
      int buf_write_len = min(cert_payload_len_in_curr_pac, remained_cert_len);
      BIO_write(bio, certInitPtr, buf_write_len);
      remained_cert_len -= buf_write_len;
      if (remained_cert_len <= 0) output_ssl_certificate(bio);
    }
  }

  // if (sslHeader->type == 22) { // SSL handshake (0x16)
  //   SSL_CTX* ctx = SSL_CTX_new(SSLv23_method());
  //   SSL* ssl = SSL_new(ctx);
  //   // BIO* bio = BIO_new(BIO_s_mem());
  //   BIO_write(bio, sslPacket, sslPacketLength);
  //   SSL_set_bio(ssl, bio, bio);

  //   X509* cert = SSL_get_peer_certificate(ssl);
  //   if (cert != nullptr) {
  //       X509_print_fp(stdout, cert); // Print certificate details to stdout
  //       X509_free(cert);
  //   }

  //   SSL_free(ssl);
  //   BIO_free(bio);
  // }
}

int extract_ssl() {
  pcap_t* pcapHandle;
  char errbuf[PCAP_ERRBUF_SIZE];

  // Open the PCAP file for reading
  pcapHandle = pcap_open_offline("../SSL.pcapng", errbuf);
  if (pcapHandle == nullptr) {
      std::cerr << "Error opening PCAP file: " << errbuf << std::endl;
      return 1;
  }

  // Loop through each packet in the PCAP file
  struct pcap_pkthdr header;
  const u_char* packet;
  int loop_num = 1;
  BIO* bio = BIO_new(BIO_s_mem());
  int remained_cert_len = -1;
  cout << "reach place 1" << endl;
  while ((packet = pcap_next(pcapHandle, &header)) != nullptr) {
    // cout << "loop_num: " << loop_num << ", packet_len: " << header.len << endl; 
    processPacket(packet, header.len, loop_num, bio, remained_cert_len);
    // if (loop_num == 3012) {
    //   // cout << "loop_num: " << loop_num << ", packet[0]: " << packet[0] << endl;
    //   // cout << "header.caplen: " << header.caplen << ", header.len: " << header.len << ", header.ts: " << header.ts.tv_usec << endl;
    //   for (int i = 0; i < header.len; ++i) {
    //     int num = (*packet) - 0;
    //     if (num == 22) {
    //       cout << "i: " << i << ", packet: " << num << endl;
    //     }
    //     ++packet;
    //   }
    // }
    ++loop_num;
  }
  BIO_free(bio);
  // Close the PCAP file
  pcap_close(pcapHandle);
  return 0;
}

int main() {
  extract_ssl();
}