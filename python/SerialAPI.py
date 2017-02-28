import threading
import time
import serial
class serial_builder():
    __clock = threading.Lock()
    __dataBase = {}
    def __init__(self):
        t1 = threading.Thread(target=self.sendSerialMessage,args=())
        t1.setDaemon(True)
        t1.start()
        
    def sendSerialMessage(self):
        t=serial.Serial('/dev/ttyACM1',9600)
        while True:
            self.__clock.acquire()
            #print 1
            #print(self.__dataBase)
            tmpstr = ''
            for i in self.__dataBase.keys():
                tmpstr = self.__buildselector(i);
                t.write(tmpstr)
                tmpstr = self.__builddata(self.__dataBase[i])
                t.write(tmpstr)
            self.__clock.release()
            #print -1
            time.sleep(0.02)
    def __buildselector(self,deviceid):
        return chr(deviceid|0b00000000)
    def __builddata(self,data):
        return chr(data|0b10000000)
    def changeData(self,key,value):
        self.__clock.acquire()
        if key > 15:
            print("key is too big !ignored")
            self.__clock.release()
            return
        if value - 128 > 127:
            print("value too big !! ignored")
            self.__clock.release()
            return
        self.__dataBase[key] = value
        self.__clock.release()
class Thruster():
    __numid = -1
    __speed4movement = 0
    __offset = 0
    __serial = serial_builder()
    def __init__(self, num,serial):
        self.__numid = num
        self.__serial = serial
    def __checkSpeed(self,num):
        #127 63
        if num > 127:
            return 127
        if num < 0:
            return 0
        return num
    def __checkOffset(self,num):
        return num
    def getSpeed4movement(self):
        return self.__speed4movement
    def getOffset(self):
        return self.__offset
    def setSpeed4movement(self,spe):
        self.__speed4movement = self.__checkSpeed(spe)
        overall=self.__checkSpeed(self.__offset+self.__speed4movement)
        self.__serial.changeData(self.__numid,overall)
    def setOffset(self,spe):
        self.__offset=self.__checkOffset(spe)
        overall=self.__checkSpeed(self.__offset+self.__speed4movement)
        self.__serial.changeData(self.__numid,overall)
         
class Basicmovement():
    __thrusters = {}
    __serial = -1
    def __init__(self,se):
        self.__thrusters['FORWARD_STARBOARD'] = Thruster(0,se)
        self.__thrusters['FORWARD_PORT'] = Thruster(1,se)
        self.__thrusters['BOW_STARBOARD'] = Thruster(2,se)
        self.__thrusters['BOW_PORT'] = Thruster(3,se)
        self.__thrusters['AFT_STARBOARD'] = Thruster(4,se)
        self.__thrusters['AFT_PORT'] = Thruster(5,se)
        self.__thrusters['TRANS_BO'] = Thruster(6,se)
        self.__thrusters['TRANS_AFT'] = Thruster(7,se)
    def forward(self,speed):
        '''speed: signed int
            should be in (-63,64)'''
        self.__thrusters['FORWARD_STARBOARD'].setSpeed4movement(speed + 63)
        self.__thrusters['FORWARD_PORT'].setSpeed4movement(speed + 63)
    def up(self,speed):
        '''speed: signed int
            should be in (-63,64)'''
        self.__thrusters['BOW_STARBOARD'].setSpeed4movement(speed + 63)
        self.__thrusters['BOW_PORT'].setSpeed4movement(speed + 63)
        self.__thrusters['AFT_STARBOARD'].setSpeed4movement(speed + 63)
        self.__thrusters['AFT_PORT'].setSpeed4movement(speed + 63)
    def turnright(self,speed):
        '''not Sure the direction!!!'''
        self.__thrusters['TRANS_BO'].setSpeed4movement(speed + 63)
        self.__thrusters['TRANS_AFT'].setSpeed4movement(speed + 63)
    def bowup(self,speed):
        self.__thrusters['BOW_STARBOARD'].setOffset(speed)
        self.__thrusters['BOW_PORT'].setOffset(speed)
        self.__thrusters['AFT_STARBOARD'].setOffset(-speed)
        self.__thrusters['AFT_PORT'].setOffset(-speed)
    def portup(self,speed):
        self.__thrusters['BOW_STARBOARD'].setOffset(-speed)
        self.__thrusters['BOW_PORT'].setOffset(speed)
        self.__thrusters['AFT_STARBOARD'].setOffset(-speed)
        self.__thrusters['AFT_PORT'].setOffset(speed)
if __name__ == '__main__':
    a = serial_builder()
    T = Thruster(1,a)
    T.setOffset(100)
    time.sleep(2)
    T.setOffset(0)
    time.sleep(1)
    move = Basicmovement(a)
    T.setOffset(55);
    time.sleep(1)
    T.setOffset(0)
    move.forward(32)
    move.portup(5)
    time.sleep(1)
    move.bowup(5)
    time.sleep(1100)
