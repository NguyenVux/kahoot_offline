import sys
import glob
import serial
import threading
from time import sleep

# handle data 
def checkbit(num, bit):
    num=int(num)>>(int(bit)-1)
    if ((num&1)!=0):
        return 1
    else:
        return 0

class kahoot_connect:
    #init system
    def __init__(self,port):
        self.connected = False
        self.port = port
        self.baud = 115200
        self.data = []
        self.streamIn = bytearray(b'')

    #start thread read from serial
    def start(self):    
        serial_port = serial.Serial(self.port, self.baud, timeout=0)
        #need check
        self.connected = True
        self.thread = threading.Thread(target=self.read_from_port, args=(serial_port,))
        self.thread.start()

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
        
        self.streamIn.append(data[0])

        if(len(self.streamIn)<9):
            return
        
        #if too long then remove head
        if(len(self.streamIn)>9):
            self.streamIn = self.streamIn[len(self.streamIn)-9:]

        #check bytes correction
        if(self.streamIn[len(self.streamIn)-2] != 0xAA or self.streamIn[len(self.streamIn)-1] != 0x0a): #custom or \n
                return

        # print("get: RAW:",self.streamIn)

        macaddr = ""
        for i in range(6):  
            macaddr += hex(self.streamIn[i])[2:] + ":"
        #remove :
        macaddr = macaddr[:len(macaddr)-1]

        output = [macaddr,checkbit(self.streamIn[6],4),checkbit(self.streamIn[6],3),checkbit(self.streamIn[6],2),checkbit(self.streamIn[6],1)]

        # print("DATA:",output)
        self.data.append(output)
        self.streamIn = bytearray(b'')

    #run as read serial thread
    def read_from_port(self,ser):
        while not self.connected:
            #serin = ser.read()
            self.connected = True
        while True:
            # print("test")
            reading = ser.read()
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
        self.data = []
        return data_return

# test code
kc  = kahoot_connect('COM7')
kc.start()

while(1):
    sleep(1)
    data = kc.readData()
    if(data != []):
        print(len(data))

print(kc.connected)