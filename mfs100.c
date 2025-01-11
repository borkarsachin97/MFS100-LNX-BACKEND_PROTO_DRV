#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>
#include <string.h>

#include "usbComm.h"

#include <gtk/gtk.h>

#define MAX_USB_SPEED 0x801c

/*
	uint16_t vid;
	uint16_t pid;
	uint8_t endPointOUT;
	uint8_t endPointIN;
	uint8_t *data;
	int sizeOfData;
	int transferred;
	int read;
	int transTime;
	int readTime;
	bool needWait;
*/

void loadDev(USB *dev)
{
	dev->vid = 0x2c0f;
	dev->pid = 0x1005;
	dev->endPointIN = 0x00;
	dev->endPointIN1 = 0x02;
	dev->endPointIN2 = 0x04;
	dev->endPointOUT = 0x80;
	dev->endPointOUT1 = 0x82;
	dev->endPointOUT2 = 0x88;
	dev->wValue = 0x0000;
	dev->wIndex = 0x0000;
	dev->bmRequestType = 0x40;
	dev->sizeOfData = MAX_USB_SPEED;
	dev->transTime = 5000;
	dev->readTime = 5000;
	dev->isDev = false;
}

/**
 * @brief Reads firmware data in chunks and prints the progress.
 *
 * This function simulates reading firmware from a device, chunk by chunk. It constructs
 * a packet for each read operation, calculates the CRC, and prints the packet contents
 * and progress. The progress is printed as a percentage, and the address is handled in
 * little-endian format for transmission.
 *
 * @param addrs     The starting address of the firmware in memory.
 * @param rdCyl     The size of each chunk to read (in bytes).
 * @param flashsize The total size of the firmware to be read (in bytes).
 * @return int      Returns 0 on success.
 */
int getFingerprint()
{
	USB dev;
    loadDev(&dev);
    libusbAPI api;
    api.handle = NULL;
    api.ctx = NULL;
    
    //int transfer_result;

    if (libusb_init(&api.ctx) != 0)
    {
        printf("Failed to initialize libusb\n");
        return 0;
    }

    printf("\n\t << Waiting for the device to be connected >>\n");
    // Check device connection
    while (!isDeviceConnected(&api, &dev)) 
    {
        printf("...\n");
        sleep(1); // Sleep for 1 second
    }
    
    //uint8_t data[pkt.size + 4];
    uint8_t *buffer = malloc(MAX_USB_SPEED);
    
    printf("mallc, ");
		dev.endPointIN1 = 0x00;
		dev.bmRequestType = 0x40;
		dev.bRequest = 0xBB;
		stConfig(&dev, &api);
		dev.bRequest = 0xBC;
		stConfig(&dev, &api);
		
		dev.data = buffer;
		//sleep(3);
		//readData(&dev, &api);
		for(int a = 0 ; a < 85; a++)
	{
		//printf("entering readData\n");
		readData(&dev, &api);
		
		printf("Read %d", dev.read);
        for (int i = 0; i < dev.read; ++i) 
        {
            printf(" %02X |", dev.data[i]);
        }

        
        
		FILE *file = fopen("fing.bin", "ab");
		if (file == NULL) 
		{
			perror("Error opening file");
			return -1;
		}

		// Write the buffer data to the file
		size_t written = fwrite(dev.data, sizeof(char), dev.read, file);
		if (written != dev.read)
		{
			perror("Error writing to file");
			fclose(file);
			return -1;
		}
		// Close the file
		fclose(file);
	}
	
	
	dev.bRequest = 0xBD; // Close the device 0xVendor
	stConfig(&dev, &api);
	free(buffer);
	libusb_close(api.handle);
    libusb_exit(api.ctx);
    // Return success
    return 0;
}

int main (int argc, char *argv[])
{
    getFingerprint();
    return 0;
}

