import cv2 as cv
import sys

img = cv.imread('soccer.jpg')

gray=cv.cvtColor(img, cv.COLOR_BGR2GRAY)

out = img.copy()
out = 255-out
cv.imshow('gray', out)
cv.waitKey()
cv.destroyAllWindows()