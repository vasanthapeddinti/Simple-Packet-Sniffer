#include <pcap.h>
#include "include/hacking.h"

void pcap_fatal(const char *failed_in, const char *errbuf) {
    printf("Fatal error in %s: %s\n", failed_in, errbuf);
}

int main() {
    struct pcap_pkthdr header;
    const unsigned char *packet;
    char errbuf[PCAP_ERRBUF_SIZE];
    char *device;
    pcap_t *pcap_handle; // similar to fd
    int i;

    device = pcap_lookupdev(errbuf);
    if (device == NULL) {
        pcap_fatal("pcap_lookupdev", errbuf);
    }
    printf("Sniffing on device %s\n", device);

    pcap_handle = pcap_open_live(device, 4096, 1, 0, errbuf);
    if (pcap_handle == NULL) {
        pcap_fatal("pcap_open_live", errbuf);
    }

    for (i = 0; i < 3; i++) {
        packet = pcap_next(pcap_handle, &header);
        printf("Got a %d byte packet\n", header.len);
        dump(packet, header.len);
    }
    pcap_close(pcap_handle);
}