from PIL import Image
import pytesseract
import cv2
import os
"""
from picamera import PiCamera
from time import sleep
cam=PiCamera()
cam.start_preview()
sleep(15)
cam.capture(image)
cam.stop_preview()
"""
image='/home/pi/Desktop/1.jpg'
preprocess = "blur"
WidthCorrection = 10
HeightCorrection  = 10
config = '--ocr 3 --psm 10'
# загрузить образ и преобразовать его в оттенки серого
image = cv2.imread(image)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# проверьте, следует ли применять пороговое значение для предварительной обработки изображения

if preprocess == "thresh":
    gray = cv2.threshold(gray, 0, 255,
        cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]

# если нужно медианное размытие, чтобы удалить шум
elif preprocess == "blur":
    gray = cv2.medianBlur(gray, 3)


# сохраним временную картинку в оттенках серого, чтобы можно было применить к ней OCR
for i in range(5):
    filename = "{}.png".format(1)
    cv2.imwrite(filename, gray)

    img = cv2.imread('/home/pi/Desktop/'+str(i)+'.png', cv2.IMREAD_UNCHANGED)
    width = int(img.shape[1] / WidthCorrection)
    height = int(img.shape[0] /HeightCorrection)
    dim = (width, height)
    resized = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)
    filename = "{}.png".format(i+1)
    cv2.imwrite(filename, resized)
    # загрузка изображения в виде объекта image Pillow, применение OCR, а затем удаление временного файла
    text =pytesseract.image_to_string(resized,lang='eng',config=config)
    print("Working")
    print(text)
    if(text=='H' or text== 'h'):
        print('i respond H')
        break
    elif(text=='s' or text=='S'):
        print('i respond S')
        break
    elif(text=='u' or text=='U'):
        print('i respond S')
        break


	

# показать выходные изображения
#cv2.imshow("Image", image)
#cv2.imshow("Output", gray)
