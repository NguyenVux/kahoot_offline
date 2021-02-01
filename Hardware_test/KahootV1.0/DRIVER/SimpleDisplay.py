# import tkinter
import tkinter as tk
import threading
import serial

def connect():
    """The function initiates the Connection to the UART device with the Port and Buad fed through the Entry
    boxes in the application.
    The radio button selects the platform, as the serial object has different key phrases 
    for Linux and Windows. Some Exceptions have been made to prevent the app from crashing,
    such as blank entry fields and value errors, this is due to the state-less-ness of the 
    UART device, the device sends data at regular intervals irrespective of the master's state.
    The other Parts are self explanatory.
    """

    version_ = button_var.get()
    print(version_)
    global serial_object
    port = port_entry.get()
    baud = baud_entry.get()
    

    try:
        if version_ == 2:
            try:
                serial_object = serial.Serial('/dev/tty' + str(port), baud)
            
            except:
                print "Cant Open Specified Port"
        elif version_ == 1:
            serial_object = serial.Serial('COM' + str(port), baud)

    except ValueError:
        print "Enter Baud and Port"
        return

    t1 = threading.Thread(target = get_data)
    t1.daemon = True
    t1.start()

def get_data():
    """This function serves the purpose of collecting data from the serial object and storing 
    the filtered data into a global variable.
    The function has been put into a thread since the serial event is a blocking function.
    """
    global serial_object
    global filter_data

    while(1):   
        try:
            serial_data = serial_object.readline().strip('\n').strip('\r')
            
            filter_data = serial_data.split(',')
            print filter_data
        
        except TypeError:
            pass

class Application(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.create_widgets()

    def create_widgets(self):
        self.hi_there = tk.Button(self)
        self.hi_there["text"] = "Hello World\n(click me)"
        self.hi_there["command"] = self.say_hi
        self.hi_there.pack(side="top")


        self.colour = tk.StringVar()
        self.colour.set('blue')

        self.c_color = 0

        self.btn = tk.Button(root, text = "Click Me", command = self.colourUpdate)
        self.l =  tk.Label(root, textvariable=self.colour, fg = self.colour.get())
        self.l.pack(side="top")
        self.btn.pack(side="top")

        self.quit = tk.Button(self, text="QUIT", fg="red",
                              command=self.master.destroy)
        self.quit.pack(side="bottom")


    def colourUpdate(self):
        if self.c_color == 0:
            self.l.config(fg='red')
            self.c_color = 1
        else:
            self.l.config(fg='blue')
            self.c_color = 0
        # self.root.update()


    def say_hi(self):
        print("hi there, everyone!")

#threads
t2 = threading.Thread(target = update_gui)
t2.daemon = True
t2.start()

root = tk.Tk()

root.geometry('400x150')  

app = Application(master=root)
app.mainloop()