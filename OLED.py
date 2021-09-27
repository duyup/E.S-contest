from PIL import Image, ImageDraw, ImageFont
from lib_oled96 import ssd1306
from time import sleep
from smbus import SMBus

i2cbus1 = SMBus(1) #GPIO를 이용할 OLED 설정
i2cbus0 = SMBus(0)
oled1 = ssd1306(i2cbus1)
oled0 = ssd1306(i2cbus0)



while 1: # 무한히 반복하여 클라이언트로부터 값을 받도록 함
    f = open("object.txt",'r') # TXT파일 오픈
    line = f.readline() # TXT파일의 문장을 읽기
    print(line)
    if line == 'person': # 사람이면 pedestrian.png 사진을 Oled에 표시
        logo1 = Image.open('pedestrian.png').convert('1')
        oled1.canvas.bitmap((0,0), logo1, fill=1)
        oled1.display() 
    elif line =='car': # 자동차면 car.png 사진을 Oled에 표시
        logo0 = Image.open('car.png').convert('1')
        oled0.canvas.bitmap((0,0), logo0, fill=1)
        oled0.display()   
    else: # 두 경우 모두 아닐때 Oled 종료
         oled0.cls()
         oled1.cls()
  
    f.close()
       

        
        







