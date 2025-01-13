# MFS100 Linux Backend Driver  

This repository provides a backend driver for the MFS100 fingerprint scanner on Linux. Currently, it supports streaming raw fingerprint data from the device and saving it to a file. This is the foundation for further development, such as converting the raw stream into fingerprint images.  

![MFS100 with red light active](images/mfs100_scanner_active.png)  
*Figure 1: MFS100 device turned on, ready for fingerprint scanning.*  

---

## Features  
- **Stream Capture**: Captures raw fingerprint data and saves it to a file.  
- **Device Initialization**: Automatically initializes the device upon connection.  

![Raw stream output in terminal](images/raw_stream_terminal.png)  
*Figure 2: Raw stream output shown in the terminal.*  

---

## Prerequisites  
1. **Linux Kernel 5.x or above**  
2. **Dependencies**:  
   - `libusb`  
   - Standard build tools (`gcc`, `make`)  

---

## Installation  
Clone the repository and compile the driver:  
```bash
git clone https://github.com/yourusername/MFS100-Linux-Backend.git  
cd MFS100-Linux-Backend  
make  
Usage
Connect the MFS100 device via USB.
Run the program to start capturing raw data:
bash
Copy code
./mfs100_backend --output /path/to/output_file.raw
Future Plans
Image Conversion: Develop software to process raw data streams into usable fingerprint images.
GUI Tool: Create a graphical interface for easier usage.
Contributions
Contributions are welcome! If you'd like to contribute, please open an issue or submit a pull request.

License
This project is licensed under the MIT License. See the LICENSE file for details.

Disclaimer
This is a work-in-progress project. It is not intended for production use.

Acknowledgments
Special thanks to the open-source community for inspiration and support!

yaml
Copy code

---

You'll need to replace `images/mfs100_scanner_active.png` and `images/raw_stream_terminal.png` with the paths to your images in the repository. Would you like help generating placeholder images or finalizing any part of the content?

