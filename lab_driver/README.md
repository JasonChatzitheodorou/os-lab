# Lunix Kernel Driver

Create a character device driver that takes measurements over a network of sensors and extracts user space data, depending on the type to sensor. Each sensor has 3 devices that measure voltage, temperature and light in /dev/lunix0-batt, /dev/lunix0-temp and /dev/lunix0-light respectively. 

The network consists of a wireless mesh of card Crossbow MPR2400CA with sensors MDA100CB and a base station MPR2400CA connected via a USB MIB520CB serial connection with a linux pc where the driver is implemented. The following is a representation of the  network.

![](/lab_driver/images/mesh.png)

The implementation functions as an extension of the already existing USB driver of linux but modified to accommodate our sensors. The driver has architectural structure the following. 

![](/lab_driver/images/arch.png)

- (a) : data captured by the base station
- (b) : moved to system over serial usb
- (c) : divert from the stand line and using a filter of line discipline of lunix
- (d) : push toward the lunix protocol
- (e) : lunix protocol that decipher that data and save the measurements to different buffers 
- (g) : the lunix character device driver
- (h) : the usage of system calls to verify the correct execution of the system with a user space application. 

---

The system call supported for the application is 
- read() : that returns the measurements from multiple processes simultaneously using locks, and sleep when no data is found. 
- mmap() : depict the measurement to a memory between the user and kernel space (memory-mapped I/O) 