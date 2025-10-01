# 🌐 Wireless Sensor Network Communication System

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![OS](https://img.shields.io/badge/OS-Contiki--NG-green.svg)](https://www.contiki-ng.org/)
[![Protocol](https://img.shields.io/badge/Protocol-UDP%2FIPv6-orange.svg)](https://en.wikipedia.org/wiki/User_Datagram_Protocol)
[![Routing](https://img.shields.io/badge/Routing-RPL-red.svg)](https://en.wikipedia.org/wiki/IPv6_Routing_Protocol_for_Low-Power_and_Lossy_Networks)

> A production-ready wireless sensor network implementation demonstrating multi-hop communication, intelligent message routing, and IoT protocol expertise using Contiki OS.

## 📋 Overview

This project implements a sophisticated **Wireless Sensor Network (WSN)** communication system designed for IoT applications requiring reliable, low-power multi-hop networking. Built on Contiki OS—a leading operating system for the Internet of Things—this system showcases advanced embedded systems programming and network architecture design.

**The Challenge:** In distributed IoT environments, sensor nodes often cannot communicate directly due to range limitations. This requires intermediate relay nodes and intelligent routing protocols to ensure reliable data transmission across the network.

**The Solution:** This implementation provides a complete three-node WSN architecture featuring a client sensor node, an intelligent relay node, and a server/sink node. The system uses UDP over IPv6 with RPL (Routing Protocol for Low-Power and Lossy Networks) to enable efficient, scalable communication suitable for real-world IoT deployments.

**What Makes This Special:** Unlike simple point-to-point communication examples, this project demonstrates production-level concepts including event-driven architecture, message validation, bidirectional relay routing, and network congestion management—all within the resource constraints of embedded systems.

## ✨ Key Features

- **🔄 Multi-Hop Communication Architecture** - Implements a relay node pattern enabling communication between nodes beyond direct radio range, demonstrating understanding of WSN topology design
- **🌍 IPv6-Ready Networking** - Full IPv6 addressing support using link-local addresses, preparing the system for internet-scale IoT deployments
- **🚀 RPL Routing Protocol** - Leverages RPL for low-power, lossy network routing with automatic root node establishment and network formation
- **⚡ Event-Driven Processing** - Utilizes Contiki's protothread architecture for efficient, non-blocking concurrent operations without traditional threading overhead
- **🔒 Message Validation & Response Handling** - Implements request-response patterns with proper message filtering and acknowledgment mechanisms
- **🎲 Network Congestion Management** - Uses randomized transmission intervals to prevent network flooding and collision in wireless channels
- **🔌 Bidirectional Relay Logic** - Intelligent intermediate node that dynamically routes messages based on source address detection
- **📊 Command & Control System** - Demonstrates IoT actuation patterns with light control commands and status feedback

## 🛠️ Tech Stack

### **Embedded Systems & OS**
- **Contiki-NG** - Real-time operating system specifically designed for IoT devices
- **C Language** - Low-level systems programming with direct hardware control
- **Protothreads** - Lightweight stackless threading for event-driven concurrency

### **Networking & Protocols**
- **UDP (User Datagram Protocol)** - Lightweight transport protocol suitable for resource-constrained devices
- **IPv6** - Next-generation internet protocol with link-local addressing
- **RPL (IPv6 Routing Protocol for LLNs)** - Industry-standard routing for low-power lossy networks
- **Simple-UDP API** - High-level Contiki networking abstraction
- **uIP Stack** - Micro IP stack for low-level network operations

### **Development & Tools**
- **Cooja Simulator** (Recommended) - Network simulation and debugging platform
- **GCC Compiler** - Cross-compilation for embedded targets
- **Git** - Version control and collaboration

## 🏗️ Architecture & Design

### System Architecture

```
┌─────────────┐         ┌─────────────┐         ┌─────────────┐
│   Mote 1    │         │  Relay Node │         │   Mote 6    │
│  (Client)   │◄───────►│(ara_dugum)  │◄───────►│  (Server)   │
│             │  UDP    │             │  UDP    │             │
│ Sensor Node │         │ Intermediate│         │  Root/Sink  │
└─────────────┘         └─────────────┘         └─────────────┘
      ▲                       ▲                       ▲
      │                       │                       │
      └───────────────────────┴───────────────────────┘
                    IPv6 Link-Local Network
                    RPL Routing Protocol
```

### Design Patterns & Principles

- **Client-Server Pattern**: Mote6 acts as root/server, Mote1 as client
- **Relay/Gateway Pattern**: Intermediate node enables multi-hop communication
- **Event-Driven Architecture**: Contiki PROCESS and callbacks for non-blocking I/O
- **Message-Based Communication**: Asynchronous UDP messaging with acknowledgments
- **Layered Network Stack**: Clean separation between application and network layers

### Key Technical Decisions

**Why Contiki OS?** Designed specifically for resource-constrained IoT devices with built-in networking stack, minimal memory footprint, and industry adoption in WSN research and commercial products.

**Why UDP over TCP?** UDP's connectionless nature reduces overhead—critical for battery-powered sensors. Acceptable packet loss is typical in WSN environments, and custom acknowledgment layers can be added at the application level.

**Why IPv6?** Provides the massive address space necessary for IoT scale, and RPL routing is IPv6-native, ensuring interoperability with modern internet infrastructure.

## 🚀 Getting Started

### Prerequisites

- **Contiki-NG** development environment (v4.0 or higher recommended)
- **GCC ARM Embedded Toolchain** or compatible compiler
- **Cooja Simulator** (for simulation testing)
- **Git** for version control
- Basic understanding of C programming and networking concepts

### Installation

1. **Clone the repository**
```bash
git clone https://github.com/ensuca/sensorCommunication.git
cd sensorCommunication
```

2. **Set up Contiki-NG** (if not already installed)
```bash
git clone https://github.com/contiki-ng/contiki-ng.git
cd contiki-ng
git submodule update --init --recursive
```

3. **Configure the environment**
```bash
export CONTIKI=/path/to/contiki-ng
```

### Building the Project

**For Cooja Simulation (Recommended for testing):**
```bash
# Each node can be compiled as a Cooja mote
make TARGET=cooja mote1
make TARGET=cooja mote6
make TARGET=cooja ara_dugum
```

**For Physical Hardware (e.g., Zolertia Z1, TelosB, etc.):**
```bash
# Example for Zolertia Z1 platform
make TARGET=z1 mote1
make TARGET=z1 mote6
make TARGET=z1 ara_dugum
```

**For Sky motes:**
```bash
make TARGET=sky mote1
make TARGET=sky mote6
make TARGET=sky ara_dugum
```

### Running the System

#### Using Cooja Simulator

1. Open Cooja: `ant run` from Contiki's tools/cooja directory
2. Create a new simulation
3. Add mote types using the compiled firmware
4. Arrange nodes in a line: Mote1 ↔ Relay ↔ Mote6
5. Start the simulation and observe the serial output

#### On Physical Hardware

1. Flash each compiled firmware to corresponding hardware nodes
2. Arrange nodes within communication range
3. Power on all nodes (Mote6/Server should start first as root)
4. Monitor via serial connection (115200 baud typically)

### Configuration

**Network Parameters** (in source files):
```c
// UDP Ports
#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678

// Message interval (60 seconds)
#define SEND_INTERVAL (60 * CLOCK_SECOND)
```

**IPv6 Addresses** (ara_dugum.c):
```c
// Modify these to match your network topology
uip_ip6addr(&first_node_ipaddr, 0xfe80, 0, 0, 0, 0x212, 0x7401, 0x1, 0x101);
uip_ip6addr(&sixth_node_ipaddr, 0xfe80, 0, 0, 0, 0x212, 0x7406, 0x6, 0x606);
```

## 💻 Usage Examples

### Expected Serial Output

**Mote1 (Client Node):**
```
[INFO: App     ] Sending request: LIGHT6: TURN_ON
[INFO: App     ] LIGHT6 SUCCESSFULLY TURNED_ON
[INFO: App     ] Sending request: LIGHT6: TURN_ON
[INFO: App     ] LIGHT6 SUCCESSFULLY TURNED_ON
[INFO: App     ] Sending request: ANY_OTHER_MESSAGES
[INFO: App     ] LIGHT6 PROCESS FAILED
```

**Mote6 (Server Node):**
```
[INFO: App     ] UDP server started
[INFO: App     ] Received: LIGHT6: TURN_ON from fe80::212:7401:1:101
[INFO: App     ] Sending response: LIGHT6: TURNED_ON
[INFO: App     ] Received: ANY_OTHER_MESSAGES from fe80::212:7401:1:101
[INFO: App     ] Sending response: WRONG REQ.
```

### Message Flow Diagram

```
Time  │ Mote1            Relay Node          Mote6
──────┼─────────────────────────────────────────────
T+0s  │ "LIGHT6: TURN_ON" ──→ Relay ──→ Processes
T+1s  │ Waiting...            Relay ←── "LIGHT6: TURNED_ON"
T+2s  │ ←── Relay ←── Forwards response
T+2s  │ "SUCCESS" logged
```

## 📁 Project Structure

```
sensorCommunication/
│
├── mote1.c              # Client sensor node (sender)
│   ├── UDP client implementation
│   ├── Periodic message transmission
│   ├── Response handling and validation
│   └── Random interval management
│
├── mote6.c              # Server/sink node (receiver)
│   ├── UDP server implementation
│   ├── RPL root node configuration
│   ├── Message processing and filtering
│   └── Response generation
│
├── ara_dugum.c          # Intermediate relay node
│   ├── Bidirectional message forwarding
│   ├── Source-based routing logic
│   ├── Static IPv6 address configuration
│   └── Low-level uIP stack usage
│
└── README.md            # Project documentation
```

### Code Highlights

**Event-Driven Client (mote1.c:48-89)**
```c
PROCESS_THREAD(udp_client_process, ev, data)
{
  static struct etimer periodic_timer;
  PROCESS_BEGIN();

  // Non-blocking timer-based transmission
  etimer_set(&periodic_timer, random_rand() % SEND_INTERVAL);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    // Send command with network reachability check
    if(NETSTACK_ROUTING.node_is_reachable()) {
      // Smart message alternation for testing
    }
  }
  PROCESS_END();
}
```

**Intelligent Relay (ara_dugum.c:32-59)**
```c
// Source-aware bidirectional routing
if(uip_ipaddr_cmp(&UIP_IP_BUF->srcipaddr, &sixth_node_ipaddr)) {
  send_to_first_node(msg);  // From server to client
} else {
  send_to_sixth_node(msg);  // From client to server
}
```

## 🔧 Network Protocol Details

### UDP Communication

| Parameter | Value | Purpose |
|-----------|-------|---------|
| Client Port | 8765 | Source port for sensor nodes |
| Server Port | 5678 | Destination port for root/sink |
| Transport | UDP | Lightweight, low-overhead protocol |
| Network Layer | IPv6 | Modern addressing with link-local scope |

### Message Protocol

**Request Format:**
```
Command: "LIGHT6: TURN_ON"
Purpose: Actuator control command
Response: "LIGHT6: TURNED_ON" (success)
```

**Test Message:**
```
Command: "ANY_OTHER_MESSAGES"
Purpose: Validation testing
Response: "WRONG REQ." (filtered)
```

## ⚡ Performance & Optimization

### Resource Efficiency
- **Memory Footprint**: Minimal RAM usage through static allocation and protothreads
- **CPU Utilization**: Event-driven model allows CPU sleep between events
- **Network Efficiency**: Randomized intervals prevent broadcast storms

### Scalability Considerations
- **Horizontal Scaling**: Architecture supports multiple client nodes with same relay pattern
- **Network Formation**: RPL automatically builds routing trees as nodes join
- **Message Overhead**: Compact string-based protocol minimizes packet size

### Power Optimization
- **Duty Cycling**: 60-second intervals allow radio sleep periods
- **Efficient Routing**: RPL minimizes hop count and retransmissions
- **Event-Driven**: No busy-waiting or polling loops waste energy

## 🧪 Testing

### Manual Testing Approach

1. **Single-Hop Test**: Deploy Mote1 and Mote6 in direct range
2. **Multi-Hop Test**: Add relay node and increase distance
3. **Message Validation**: Verify "WRONG REQ." response for invalid commands
4. **Network Formation**: Observe RPL DODAG formation in logs

### Expected Behavior

✅ Mote6 successfully becomes RPL root node
✅ Mote1 discovers route to Mote6 through relay
✅ 4 out of 5 messages receive "TURNED_ON" response
✅ 1 out of 5 messages (test message) receives "WRONG REQ."
✅ Relay successfully forwards in both directions

### Debugging Tips

```bash
# Enable detailed network logs
#define LOG_LEVEL LOG_LEVEL_DBG

# Monitor RPL routing table
#include "net/routing/routing.h"
// Check routing state with NETSTACK_ROUTING debug output
```

## 🚀 Deployment

### Simulation Deployment (Cooja)

**Recommended Node Placement:**
- Distance between nodes: 50-100m (simulation units)
- Transmission range: Adjust to require relay node
- Interference: Enable for realistic wireless conditions

### Real-World Hardware Deployment

**Supported Platforms:**
- Zolertia Z1
- TelosB (Sky)
- OpenMote
- CC2650 SensorTag
- nRF52840 DK

**Deployment Checklist:**
1. ✅ Flash root node (Mote6) first and verify startup
2. ✅ Flash relay node and verify network join
3. ✅ Flash client nodes last
4. ✅ Monitor serial output for RPL formation
5. ✅ Verify message transmission in both directions

## 🗺️ Roadmap & Future Enhancements

### Planned Features
- [ ] **Security Layer**: DTLS encryption for secure UDP communication
- [ ] **Dynamic Routing**: Replace static addresses with RPL-based discovery
- [ ] **Multiple Sensors**: Extend to 10+ node mesh network topology
- [ ] **CoAP Protocol**: Migrate to CoAP for RESTful IoT communication
- [ ] **Data Aggregation**: Implement in-network data fusion at relay nodes
- [ ] **Energy Monitoring**: Add power consumption profiling and reporting
- [ ] **Mobile Node Support**: Handle node mobility with RPL optimizations
- [ ] **Web Dashboard**: Real-time visualization of network topology and data

### Known Limitations & Solutions
- **Static Addressing**: Currently uses hardcoded IPv6 addresses
  - *Solution*: Implement IPv6 neighbor discovery or DNS-SD
- **Single Relay**: Topology limited to linear three-node setup
  - *Solution*: RPL already supports mesh; extend application logic for multi-relay
- **No Persistence**: Messages not stored if node offline
  - *Solution*: Add queueing mechanism with retransmission

## 📄 License

This project is open source and available for educational and research purposes.

## 🤝 Contributing

This project was developed as an academic group project demonstrating WSN concepts. Contributions for educational improvements are welcome:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -m 'Add educational enhancement'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

## 👨‍💻 Author & Connect

**Enes Uca**
Embedded Systems & IoT Developer

[![Portfolio](https://img.shields.io/badge/Portfolio-ensuca.github.io-blue?style=flat-square&logo=google-chrome)](https://ensuca.github.io/ensuca.githubio)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Enes_Uca-0077B5?style=flat-square&logo=linkedin)](https://www.linkedin.com/in/enes-uca-41039327b)
[![GitHub](https://img.shields.io/badge/GitHub-ensuca-181717?style=flat-square&logo=github)](https://github.com/ensuca)

💼 Open to opportunities in embedded systems, IoT development, and wireless sensor networks.

---

## 📚 Technical References

- [Contiki-NG Documentation](https://docs.contiki-ng.org/)
- [RFC 6550 - RPL Protocol](https://tools.ietf.org/html/rfc6550)
- [IPv6 over Low-Power Wireless Networks](https://tools.ietf.org/html/rfc6282)

---

# 🇹🇷 Türkçe

# 🌐 Kablosuz Sensör Ağı İletişim Sistemi

[![Dil](https://img.shields.io/badge/Dil-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![İşletim Sistemi](https://img.shields.io/badge/İşletim_Sistemi-Contiki--NG-green.svg)](https://www.contiki-ng.org/)
[![Protokol](https://img.shields.io/badge/Protokol-UDP%2FIPv6-orange.svg)](https://en.wikipedia.org/wiki/User_Datagram_Protocol)
[![Yönlendirme](https://img.shields.io/badge/Yönlendirme-RPL-red.svg)](https://en.wikipedia.org/wiki/IPv6_Routing_Protocol_for_Low-Power_and_Lossy_Networks)

> Contiki OS kullanarak çok atlamalı iletişim, akıllı mesaj yönlendirme ve IoT protokol uzmanlığını gösteren üretime hazır bir kablosuz sensör ağı implementasyonu.

## 📋 Genel Bakış

Bu proje, güvenilir ve düşük güç tüketimli çok atlamalı ağ gerektiren IoT uygulamaları için tasarlanmış gelişmiş bir **Kablosuz Sensör Ağı (KSA)** iletişim sistemini uygulamaktadır. Nesnelerin İnterneti için önde gelen bir işletim sistemi olan Contiki OS üzerine inşa edilen bu sistem, ileri düzey gömülü sistemler programlama ve ağ mimarisi tasarımını sergilemektedir.

**Problem:** Dağıtık IoT ortamlarında, sensör düğümleri menzil sınırlamaları nedeniyle çoğu zaman doğrudan iletişim kuramazlar. Bu, ağ genelinde güvenilir veri iletimini sağlamak için ara röle düğümleri ve akıllı yönlendirme protokolleri gerektirir.

**Çözüm:** Bu implementasyon, bir istemci sensör düğümü, akıllı bir röle düğümü ve bir sunucu/havuz düğümünden oluşan eksiksiz üç düğümlü bir KSA mimarisi sağlar. Sistem, gerçek dünya IoT dağıtımlarına uygun verimli ve ölçeklenebilir iletişimi sağlamak için RPL (Düşük Güçlü ve Kayıplı Ağlar için Yönlendirme Protokolü) ile IPv6 üzerinden UDP kullanır.

**Özel Kılan Nedir:** Basit noktadan noktaya iletişim örneklerinin aksine, bu proje olay güdümlü mimari, mesaj doğrulama, çift yönlü röle yönlendirme ve ağ tıkanıklığı yönetimi gibi üretim düzeyinde kavramları—tümü gömülü sistemlerin kaynak kısıtlamaları içinde—göstermektedir.

## ✨ Temel Özellikler

- **🔄 Çok Atlamalı İletişim Mimarisi** - Doğrudan radyo menzili dışındaki düğümler arasında iletişimi mümkün kılan bir röle düğüm deseni uygular ve KSA topoloji tasarımı anlayışını gösterir
- **🌍 IPv6 Uyumlu Ağ** - Link-local adresler kullanarak tam IPv6 adresleme desteği, sistemi internet ölçeğinde IoT dağıtımları için hazırlar
- **🚀 RPL Yönlendirme Protokolü** - Otomatik kök düğüm oluşturma ve ağ formasyonu ile düşük güçlü, kayıplı ağ yönlendirmesi için RPL'den yararlanır
- **⚡ Olay Güdümlü İşleme** - Geleneksel thread yükü olmadan verimli, engellemesiz eşzamanlı işlemler için Contiki'nin protothread mimarisini kullanır
- **🔒 Mesaj Doğrulama ve Yanıt İşleme** - Uygun mesaj filtreleme ve onaylama mekanizmaları ile istek-yanıt desenlerini uygular
- **🎲 Ağ Tıkanıklığı Yönetimi** - Kablosuz kanallarda ağ taşmasını ve çakışmayı önlemek için rastgele iletim aralıkları kullanır
- **🔌 Çift Yönlü Röle Mantığı** - Kaynak adres algılamasına dayalı olarak mesajları dinamik olarak yönlendiren akıllı ara düğüm
- **📊 Komuta ve Kontrol Sistemi** - Işık kontrol komutları ve durum geri bildirimi ile IoT aktüasyon desenlerini gösterir

## 🛠️ Teknoloji Yığını

### **Gömülü Sistemler ve İşletim Sistemi**
- **Contiki-NG** - IoT cihazları için özel olarak tasarlanmış gerçek zamanlı işletim sistemi
- **C Dili** - Doğrudan donanım kontrolü ile düşük seviyeli sistem programlama
- **Protothreads** - Olay güdümlü eşzamanlılık için hafif yığınsız iş parçacığı

### **Ağ ve Protokoller**
- **UDP (Kullanıcı Datagram Protokolü)** - Kaynak kısıtlı cihazlar için uygun hafif taşıma protokolü
- **IPv6** - Link-local adresleme ile yeni nesil internet protokolü
- **RPL (LLN'ler için IPv6 Yönlendirme Protokolü)** - Düşük güçlü kayıplı ağlar için endüstri standardı yönlendirme
- **Simple-UDP API** - Üst düzey Contiki ağ soyutlaması
- **uIP Yığını** - Düşük seviyeli ağ işlemleri için mikro IP yığını

### **Geliştirme ve Araçlar**
- **Cooja Simülatörü** (Önerilir) - Ağ simülasyonu ve hata ayıklama platformu
- **GCC Derleyici** - Gömülü hedefler için çapraz derleme
- **Git** - Versiyon kontrolü ve işbirliği

## 🏗️ Mimari ve Tasarım

### Sistem Mimarisi

```
┌─────────────┐         ┌─────────────┐         ┌─────────────┐
│   Mote 1    │         │ Röle Düğümü │         │   Mote 6    │
│  (İstemci)  │◄───────►│(ara_dugum)  │◄───────►│  (Sunucu)   │
│             │  UDP    │             │  UDP    │             │
│Sensör Düğümü│         │    Ara      │         │  Kök/Havuz  │
└─────────────┘         └─────────────┘         └─────────────┘
      ▲                       ▲                       ▲
      │                       │                       │
      └───────────────────────┴───────────────────────┘
                 IPv6 Link-Local Ağ
                  RPL Yönlendirme Protokolü
```

### Tasarım Desenleri ve İlkeleri

- **İstemci-Sunucu Deseni**: Mote6 kök/sunucu, Mote1 istemci olarak görev yapar
- **Röle/Ağ Geçidi Deseni**: Ara düğüm çok atlamalı iletişimi mümkün kılar
- **Olay Güdümlü Mimari**: Engellemesiz G/Ç için Contiki PROCESS ve callback'ler
- **Mesaj Tabanlı İletişim**: Onaylamalar ile asenkron UDP mesajlaşma
- **Katmanlı Ağ Yığını**: Uygulama ve ağ katmanları arasında temiz ayrım

### Önemli Teknik Kararlar

**Neden Contiki OS?** Yerleşik ağ yığını, minimal bellek ayak izi ve KSA araştırma ve ticari ürünlerinde endüstri kabulü ile kaynak kısıtlı IoT cihazları için özel olarak tasarlanmıştır.

**Neden TCP yerine UDP?** UDP'nin bağlantısız yapısı ek yükü azaltır—pille çalışan sensörler için kritiktir. Kabul edilebilir paket kaybı KSA ortamlarında tipiktir ve özel onaylama katmanları uygulama seviyesinde eklenebilir.

**Neden IPv6?** IoT ölçeği için gerekli olan büyük adres alanını sağlar ve RPL yönlendirme IPv6'ya özgüdür, modern internet altyapısı ile birlikte çalışabilirlik sağlar.

## 🚀 Başlarken

### Ön Gereksinimler

- **Contiki-NG** geliştirme ortamı (v4.0 veya üstü önerilir)
- **GCC ARM Embedded Toolchain** veya uyumlu derleyici
- **Cooja Simülatörü** (simülasyon testi için)
- **Git** versiyon kontrolü için
- C programlama ve ağ kavramları hakkında temel anlayış

### Kurulum

1. **Depoyu klonlayın**
```bash
git clone https://github.com/ensuca/sensorCommunication.git
cd sensorCommunication
```

2. **Contiki-NG'yi kurun** (henüz kurulu değilse)
```bash
git clone https://github.com/contiki-ng/contiki-ng.git
cd contiki-ng
git submodule update --init --recursive
```

3. **Ortamı yapılandırın**
```bash
export CONTIKI=/path/to/contiki-ng
```

### Projeyi Derleme

**Cooja Simülasyonu için (Test için önerilir):**
```bash
# Her düğüm bir Cooja mote olarak derlenebilir
make TARGET=cooja mote1
make TARGET=cooja mote6
make TARGET=cooja ara_dugum
```

**Fiziksel Donanım için (örn. Zolertia Z1, TelosB, vb.):**
```bash
# Zolertia Z1 platformu için örnek
make TARGET=z1 mote1
make TARGET=z1 mote6
make TARGET=z1 ara_dugum
```

**Sky mote'lar için:**
```bash
make TARGET=sky mote1
make TARGET=sky mote6
make TARGET=sky ara_dugum
```

### Sistemi Çalıştırma

#### Cooja Simülatörünü Kullanma

1. Cooja'yı açın: Contiki'nin tools/cooja dizininden `ant run`
2. Yeni bir simülasyon oluşturun
3. Derlenmiş firmware kullanarak mote tipleri ekleyin
4. Düğümleri bir çizgi halinde yerleştirin: Mote1 ↔ Röle ↔ Mote6
5. Simülasyonu başlatın ve seri çıktıyı gözlemleyin

#### Fiziksel Donanımda

1. Her derlenmiş firmware'i ilgili donanım düğümlerine yükleyin
2. Düğümleri iletişim menzili içinde yerleştirin
3. Tüm düğümleri açın (Mote6/Sunucu ilk olarak kök olarak başlamalı)
4. Seri bağlantı üzerinden izleyin (genellikle 115200 baud)

### Yapılandırma

**Ağ Parametreleri** (kaynak dosyalarda):
```c
// UDP Portları
#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678

// Mesaj aralığı (60 saniye)
#define SEND_INTERVAL (60 * CLOCK_SECOND)
```

**IPv6 Adresleri** (ara_dugum.c):
```c
// Bunları ağ topolojinize uyacak şekilde değiştirin
uip_ip6addr(&first_node_ipaddr, 0xfe80, 0, 0, 0, 0x212, 0x7401, 0x1, 0x101);
uip_ip6addr(&sixth_node_ipaddr, 0xfe80, 0, 0, 0, 0x212, 0x7406, 0x6, 0x606);
```

## 💻 Kullanım Örnekleri

### Beklenen Seri Çıktı

**Mote1 (İstemci Düğümü):**
```
[INFO: App     ] İstek gönderiliyor: LIGHT6: TURN_ON
[INFO: App     ] LIGHT6 BAŞARIYLA AÇILDI
[INFO: App     ] İstek gönderiliyor: LIGHT6: TURN_ON
[INFO: App     ] LIGHT6 BAŞARIYLA AÇILDI
[INFO: App     ] İstek gönderiliyor: ANY_OTHER_MESSAGES
[INFO: App     ] LIGHT6 İŞLEMİ BAŞARISIZ
```

**Mote6 (Sunucu Düğümü):**
```
[INFO: App     ] UDP sunucusu başlatıldı
[INFO: App     ] Alındı: LIGHT6: TURN_ON - fe80::212:7401:1:101
[INFO: App     ] Yanıt gönderiliyor: LIGHT6: TURNED_ON
[INFO: App     ] Alındı: ANY_OTHER_MESSAGES - fe80::212:7401:1:101
[INFO: App     ] Yanıt gönderiliyor: WRONG REQ.
```

### Mesaj Akış Diyagramı

```
Zaman │ Mote1            Röle Düğümü         Mote6
──────┼─────────────────────────────────────────────
T+0s  │ "LIGHT6: TURN_ON" ──→ Röle ──→ İşler
T+1s  │ Bekliyor...           Röle ←── "LIGHT6: TURNED_ON"
T+2s  │ ←── Röle ←── Yanıtı iletir
T+2s  │ "BAŞARI" kaydedildi
```

## 📁 Proje Yapısı

```
sensorCommunication/
│
├── mote1.c              # İstemci sensör düğümü (gönderici)
│   ├── UDP istemci implementasyonu
│   ├── Periyodik mesaj iletimi
│   ├── Yanıt işleme ve doğrulama
│   └── Rastgele aralık yönetimi
│
├── mote6.c              # Sunucu/havuz düğümü (alıcı)
│   ├── UDP sunucu implementasyonu
│   ├── RPL kök düğüm yapılandırması
│   ├── Mesaj işleme ve filtreleme
│   └── Yanıt üretimi
│
├── ara_dugum.c          # Ara röle düğümü
│   ├── Çift yönlü mesaj iletme
│   ├── Kaynak tabanlı yönlendirme mantığı
│   ├── Statik IPv6 adres yapılandırması
│   └── Düşük seviyeli uIP yığın kullanımı
│
└── README.md            # Proje dokümantasyonu
```

### Kod Vurguları

**Olay Güdümlü İstemci (mote1.c:48-89)**
```c
PROCESS_THREAD(udp_client_process, ev, data)
{
  static struct etimer periodic_timer;
  PROCESS_BEGIN();

  // Engellemesiz zamanlayıcı tabanlı iletim
  etimer_set(&periodic_timer, random_rand() % SEND_INTERVAL);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    // Ağ erişilebilirlik kontrolü ile komut gönder
    if(NETSTACK_ROUTING.node_is_reachable()) {
      // Test için akıllı mesaj alternasyonu
    }
  }
  PROCESS_END();
}
```

**Akıllı Röle (ara_dugum.c:32-59)**
```c
// Kaynak farkındalıklı çift yönlü yönlendirme
if(uip_ipaddr_cmp(&UIP_IP_BUF->srcipaddr, &sixth_node_ipaddr)) {
  send_to_first_node(msg);  // Sunucudan istemciye
} else {
  send_to_sixth_node(msg);  // İstemciden sunucuya
}
```

## 🔧 Ağ Protokol Detayları

### UDP İletişimi

| Parametre | Değer | Amaç |
|-----------|-------|------|
| İstemci Portu | 8765 | Sensör düğümleri için kaynak port |
| Sunucu Portu | 5678 | Kök/havuz için hedef port |
| Taşıma | UDP | Hafif, düşük yük protokolü |
| Ağ Katmanı | IPv6 | Link-local kapsam ile modern adresleme |

### Mesaj Protokolü

**İstek Formatı:**
```
Komut: "LIGHT6: TURN_ON"
Amaç: Aktüatör kontrol komutu
Yanıt: "LIGHT6: TURNED_ON" (başarı)
```

**Test Mesajı:**
```
Komut: "ANY_OTHER_MESSAGES"
Amaç: Doğrulama testi
Yanıt: "WRONG REQ." (filtrelendi)
```

## ⚡ Performans ve Optimizasyon

### Kaynak Verimliliği
- **Bellek Ayak İzi**: Statik tahsis ve protothread'ler aracılığıyla minimal RAM kullanımı
- **CPU Kullanımı**: Olay güdümlü model, olaylar arasında CPU uykusuna izin verir
- **Ağ Verimliliği**: Rastgele aralıklar broadcast fırtınalarını önler

### Ölçeklenebilirlik Hususları
- **Yatay Ölçekleme**: Mimari, aynı röle deseni ile birden çok istemci düğümünü destekler
- **Ağ Oluşumu**: RPL, düğümler katıldıkça otomatik olarak yönlendirme ağaçları oluşturur
- **Mesaj Yükü**: Kompakt string tabanlı protokol paket boyutunu minimumda tutar

### Güç Optimizasyonu
- **Görev Döngüsü**: 60 saniyelik aralıklar radyo uyku dönemlerine izin verir
- **Verimli Yönlendirme**: RPL, atlama sayısını ve yeniden iletimleri minimize eder
- **Olay Güdümlü**: Meşgul bekleme veya yoklama döngüleri enerji harcamaz

## 🧪 Test

### Manuel Test Yaklaşımı

1. **Tek Atlamalı Test**: Mote1 ve Mote6'yı doğrudan menzilde dağıtın
2. **Çok Atlamalı Test**: Röle düğümü ekleyin ve mesafeyi artırın
3. **Mesaj Doğrulama**: Geçersiz komutlar için "WRONG REQ." yanıtını doğrulayın
4. **Ağ Oluşumu**: Loglar içinde RPL DODAG oluşumunu gözlemleyin

### Beklenen Davranış

✅ Mote6 başarıyla RPL kök düğümü olur
✅ Mote1, röle üzerinden Mote6'ya rota bulur
✅ 5 mesajdan 4'ü "TURNED_ON" yanıtı alır
✅ 5 mesajdan 1'i (test mesajı) "WRONG REQ." alır
✅ Röle her iki yönde başarıyla iletir

### Hata Ayıklama İpuçları

```bash
# Detaylı ağ loglarını etkinleştir
#define LOG_LEVEL LOG_LEVEL_DBG

# RPL yönlendirme tablosunu izle
#include "net/routing/routing.h"
// NETSTACK_ROUTING debug çıktısı ile yönlendirme durumunu kontrol et
```

## 🚀 Dağıtım

### Simülasyon Dağıtımı (Cooja)

**Önerilen Düğüm Yerleşimi:**
- Düğümler arası mesafe: 50-100m (simülasyon birimleri)
- İletim menzili: Röle düğümü gerektirmek için ayarlayın
- Girişim: Gerçekçi kablosuz koşullar için etkinleştirin

### Gerçek Dünya Donanım Dağıtımı

**Desteklenen Platformlar:**
- Zolertia Z1
- TelosB (Sky)
- OpenMote
- CC2650 SensorTag
- nRF52840 DK

**Dağıtım Kontrol Listesi:**
1. ✅ Önce kök düğümü (Mote6) yükleyin ve başlatmayı doğrulayın
2. ✅ Röle düğümünü yükleyin ve ağa katılımı doğrulayın
3. ✅ İstemci düğümlerini en son yükleyin
4. ✅ RPL oluşumu için seri çıktıyı izleyin
5. ✅ Her iki yönde mesaj iletimini doğrulayın

## 🗺️ Yol Haritası ve Gelecek Geliştirmeler

### Planlanan Özellikler
- [ ] **Güvenlik Katmanı**: Güvenli UDP iletişimi için DTLS şifreleme
- [ ] **Dinamik Yönlendirme**: Statik adresleri RPL tabanlı keşif ile değiştir
- [ ] **Çoklu Sensörler**: 10+ düğüm mesh ağ topolojisine genişlet
- [ ] **CoAP Protokolü**: RESTful IoT iletişimi için CoAP'a geçiş
- [ ] **Veri Birleştirme**: Röle düğümlerinde ağ içi veri füzyonu uygula
- [ ] **Enerji İzleme**: Güç tüketimi profilleme ve raporlama ekle
- [ ] **Mobil Düğüm Desteği**: RPL optimizasyonları ile düğüm hareketliliğini ele al
- [ ] **Web Kontrol Paneli**: Ağ topolojisi ve verinin gerçek zamanlı görselleştirmesi

### Bilinen Sınırlamalar ve Çözümler
- **Statik Adresleme**: Şu anda sabit kodlanmış IPv6 adresleri kullanıyor
  - *Çözüm*: IPv6 komşu keşfi veya DNS-SD uygula
- **Tek Röle**: Topoloji lineer üç düğümlü kurulum ile sınırlı
  - *Çözüm*: RPL zaten mesh'i destekliyor; uygulama mantığını çoklu röle için genişlet
- **Kalıcılık Yok**: Düğüm çevrimdışıysa mesajlar saklanmıyor
  - *Çözüm*: Yeniden iletim ile kuyruk mekanizması ekle

## 📄 Lisans

Bu proje açık kaynak olup eğitim ve araştırma amaçları için kullanılabilir.

## 🤝 Katkıda Bulunma

Bu proje, KSA kavramlarını gösteren akademik bir grup projesi olarak geliştirilmiştir. Eğitimsel iyileştirmeler için katkılar kabul edilir:

1. Depoyu fork edin
2. Bir özellik dalı oluşturun (`git checkout -b feature/iyilestirme`)
3. Değişikliklerinizi commit edin (`git commit -m 'Eğitimsel geliştirme ekle'`)
4. Dalı push edin (`git push origin feature/iyilestirme`)
5. Bir Pull Request açın

## 👨‍💻 Yazar ve İletişim

**Enes Uca**
Gömülü Sistemler ve IoT Geliştirici

[![Portfolio](https://img.shields.io/badge/Portfolio-ensuca.github.io-blue?style=flat-square&logo=google-chrome)](https://ensuca.github.io/ensuca.githubio)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Enes_Uca-0077B5?style=flat-square&logo=linkedin)](https://www.linkedin.com/in/enes-uca-41039327b)
[![GitHub](https://img.shields.io/badge/GitHub-ensuca-181717?style=flat-square&logo=github)](https://github.com/ensuca)

💼 Gömülü sistemler, IoT geliştirme ve kablosuz sensör ağları alanında fırsatlara açığım.

---

## 📚 Teknik Referanslar

- [Contiki-NG Dokümantasyonu](https://docs.contiki-ng.org/)
- [RFC 6550 - RPL Protokolü](https://tools.ietf.org/html/rfc6550)
- [Düşük Güçlü Kablosuz Ağlar Üzerinde IPv6](https://tools.ietf.org/html/rfc6282)

---

**⭐ Eğer bu proje size ilham verdiyse, yıldız vermeyi unutmayın!**
