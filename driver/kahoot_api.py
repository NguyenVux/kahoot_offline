import sys
import glob
import serial
import threading
from time import sleep



class kahoot_connect:
    #init system
    def __init__(self,port):
        self.connected = False
        self.port = port
        self.baud = 115200
        self.data = []

    #start thread read from serial
    def start(self):    
        serial_port = serial.Serial(self.port, self.baud, timeout=0)
        self.thread = threading.Thread(target=self.read_from_port, args=(serial_port,))
        self.thread.start()
    
    # handle data 
    def checkbit(n, k):
        if n & (1 << (k - 1)):
            return 1
        else:
            return 0
    """
    INPUT:
        bytes: 0 1 2 3 4 5 6
                [   mac   ] button
    OUTPUT:
        [     MAC addr       buttons]
        ["FA:FA:FA:FA:FA:FA",0,0,0,0]
    """
    # decript and put data into list
    def handle_data(self,data):
        #debug
        print("get: RAW:",data.decode(),end=" ")

        if(len(data)!=7):
            return
        macaddr = ""
        for i in range(6):
            macaddr += data[i].hex() + ":"
        #remove :
        macaddr = macaddr[:len(macaddr)-1]

        output = [macaddr,checkbit(data[6],3),checkbit(data[6],2),checkbit(data[6],1),checkbit(data[6],0)]
        print("DATA:",output)
        self.data.append(output)

    #run as read serial thread
    def read_from_port(self,ser):
        while not self.connected:
            #serin = ser.read()
            self.connected = True
        while True:
            # print("test")
            reading = ser.readline()
            if(len(reading)!=0):
                self.handle_data(reading)

    #return all availble port
    def serial_ports(self):
        """ Lists serial port names

            :raises EnvironmentError:
                On unsupported or unknown platforms
            :returns:
                A list of the serial ports available on the system
        """
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
            # this excludes your current terminal "/dev/tty"
            ports = glob.glob('/dev/tty[A-Za-z]*')
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')

        result = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        return result

    #return data and clear cache
    def readData(self):
        data_return = self.data.copy()
        return data_return

# test code
kc  = kahoot_connect('COM4')
kc.start()

while(1):
    sleep(1)
    print(kc.readData())

print(kc.connected)
