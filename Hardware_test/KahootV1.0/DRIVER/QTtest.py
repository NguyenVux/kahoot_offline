# from PyQt5.QtCore import Qt
# from PyQt5.QtGui import QPalette
# from PyQt5.QtWidgets import QApplication, QPushButton

# app = QApplication([])
# app.setStyle('Fusion')
# palette = QPalette()
# palette.setColor(QPalette.ButtonText, Qt.red)
# app.setPalette(palette)
# button = QPushButton('Hello World')
# button.show()

# app.exec_()

# importing libraries 

# #############################################
# from PyQt5.QtWidgets import * 
# from PyQt5.QtGui import * 
# from PyQt5.QtCore import * 
# from QtSerialPort.QtCore import * 
# import sys 
  
  
# class Window(QMainWindow): 
#     def __init__(self): 
#         super().__init__() 
  
#         # setting title 
#         self.setWindowTitle("Python ") 
  
#         # setting geometry 
#         self.setGeometry(100, 100, 600, 400) 
  
#         # calling method 
#         self.UiComponents() 
  
#         # showing all the widgets 
#         self.show() 
  
#     # method for widgets 
#     def UiComponents(self): 
  
#         # creating a push button 
#         self.button = QPushButton("CLICK", self) 
  
#         # setting geometry of button 
#         self.button.setGeometry(200, 150, 100, 40) 
  
#         # changing color of button 
#         self.button.setStyleSheet("background-color : yellow") 
  
#         # adding action to a button 
#         self.button.clicked.connect(self.clickme) 
  
#     # action method 
#     def clickme(self): 
        
#         self.button.setStyleSheet("background-color : green") 
#         # printing pressed 
#         print("pressed") 
  
# # create pyqt5 app 
# App = QApplication(sys.argv) 
  
# # create the instance of our Window 
# window = Window() 
  
# # start the app 
# sys.exit(App.exec()) 


from PyQt5 import QtCore, QtWidgets, QtSerialPort

class Widget(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super(Widget, self).__init__(parent)
        self.message_le = QtWidgets.QLineEdit()
        self.send_btn = QtWidgets.QPushButton(
            text="Send",
            clicked=self.send
        )
        self.output_te = QtWidgets.QTextEdit(readOnly=True)
        self.button = QtWidgets.QPushButton(
            text="Connect", 
            checkable=True,
            toggled=self.on_toggled
        )
        # self.lable = QtWidgets.QPushButton(
        #     text="Connect", 
        #     checkable=True,
        #     toggled=self.on_toggled
        # )
        
        lay = QtWidgets.QVBoxLayout(self)
        hlay = QtWidgets.QHBoxLayout()
        hlay.addWidget(self.message_le)
        hlay.addWidget(self.send_btn)
        lay.addLayout(hlay)
        lay.addWidget(self.output_te)
        lay.addWidget(self.button)



        self.serial = QtSerialPort.QSerialPort(
            'COM8',
            baudRate=QtSerialPort.QSerialPort.Baud115200,
            readyRead=self.receive
        )

    @QtCore.pyqtSlot()
    def receive(self):
        while self.serial.canReadLine():
            text = self.serial.readLine().data().decode()
            text = text.rstrip('\n')
            self.output_te.append(text)

    @QtCore.pyqtSlot()
    def send(self):
        self.serial.write(self.message_le.text().encode())

    @QtCore.pyqtSlot(bool)
    def on_toggled(self, checked):
        self.button.setText("Disconnect" if checked else "Connect")
        if checked:
            if not self.serial.isOpen():
                if not self.serial.open(QtCore.QIODevice.ReadWrite):
                    self.button.setChecked(False)
        else:
            self.serial.close()

if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    w = Widget()
    w.show()
    sys.exit(app.exec_())