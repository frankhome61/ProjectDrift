import threading
import time
class serial_builder():
    __clock=threading.Lock()
    __dataBase={}
    def __init__(self):
        t1 = threading.Thread(target=self.sendSerialMessage,args=())
        t1.setDaemon(True)
        t1.start()
    def sendSerialMessage(self):
        while True:
            self.__clock.acquire()
            #print 1
            print (self.__dataBase)
            tmpstr=''
            for i in range(len(self.__dataBase.keys())):
                tmpstr=chr(self.__dataBase.keys()[i])
                #print tmpstr
                tmpstr=chr(self.__dataBase[self.__dataBase.keys()[i]])
                #print tmpstr
            self.__clock.release()
            #print -1
            time.sleep(0.02)
            
    def changeData(self,key,value):
        self.__clock.acquire()
        #print 2
        if key>15:
            print("key is too big !ignored")
            self.__clock.release()
            #print -2
            return
        if value-128 > 127:
            print("value too big !! ignored")
            self.__clock.release()
            #print -2
            return
        self.__dataBase[key]=value
        self.__clock.release()
        #print -2
if __name__ == '__main__':
    a=serial_builder()
    a.changeData(0b00000001,0b10011111)
    time.sleep(2)
    a.changeData(0b00000011,0b10011111)
    a.changeData(0b00000001,0b10111111)
    time.sleep(11)
