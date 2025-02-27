import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from IPython.display import display, Math, Latex
import numpy as np

plt.rcParams["font.family"] = "monospace"

def mapping(x, k):
    return  k*x

plt.figure(figsize=(11,11))
plt.title(r"Зависимость частоты от n номера гармоники")
plt.ylabel("Частота, Гц")
plt.xlabel("n")

#-------------------------------------------------------------------------------------
x = []
y1 = []
y2 = []

file = open('C://users/User/Documents/Mipt/labs/1.4.5/1.txt', 'r')
while (line := file.readline()):
  s = line.split()
  if (len(s) != 0):
    x.append(float(s[0].replace(',','.')))
    y1.append(float(s[1].replace(',','.')))
    y2.append(float(s[2].replace(',','.')))

k1 = 0
k2 = 0
summ = 0

for i in range(len(y2)):
  summ = y2[i]

print(summ/10)
coeffs,_ = curve_fit(mapping, x, y1)
k1 = coeffs
y1_fit = []
for i in range(len(x)):
  y1_fit.append(k1 * x[i])

coeffs,_ = curve_fit(mapping, x, y2)
k2 = coeffs
y2_fit = []
for i in range(len(x)):
  y2_fit.append(k2 * x[i])

plt.plot(x, y2, 'r^', label='Частота от номера гармоники реальная')
plt.plot(x, y2_fit, color = 'y', label = f"1: Реальная прямая(с аппроксимацией) " r'' f", u = {k2[0]:.3f}")

plt.plot(x, y1_fit, color = '0', label=f"Расчетный(идеальный) график u = {k1[0]:.3f}", linestyle='dashed')
#--------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------
x = []
y1 = []
y2 = []

file = open('C://users/User/Documents/Mipt/labs/1.4.5/2.txt', 'r')
while (line := file.readline()):
  s = line.split()
  if (len(s) != 0):
    x.append(float(s[0].replace(',','.')))
    y1.append(float(s[1].replace(',','.')))
    y2.append(float(s[2].replace(',','.')))

k1 = 0
k2 = 0

coeffs,_ = curve_fit(mapping, x, y1)
k1 = coeffs
y1_fit = []
for i in range(len(x)):
  y1_fit.append(k1 * x[i])

coeffs,_ = curve_fit(mapping, x, y2)
k2 = coeffs
y2_fit = []
for i in range(len(x)):
  y2_fit.append(k2 * x[i])

plt.plot(x, y2, 'r^', label='Частота от номера гармоники реальная')
plt.plot(x, y2_fit, color = 'c', label = f"2: Реальная прямая(с аппроксимацией) " r'' f", u = {k2[0]:.3f}")

plt.plot(x, y1_fit, color = '0', label= f"Расчетный(идеальный) график u = {k1[0]:.3f}", linestyle='dashed')
#--------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------
x = []
y1 = []
y2 = []

file = open('C://users/User/Documents/Mipt/labs/1.4.5/3.txt', 'r')
while (line := file.readline()):
  s = line.split()
  if (len(s) != 0):
    x.append(float(s[0].replace(',','.')))
    y1.append(float(s[1].replace(',','.')))
    y2.append(float(s[2].replace(',','.')))

k1 = 0
k2 = 0

coeffs,_ = curve_fit(mapping, x, y1)
k1 = coeffs
y1_fit = []
for i in range(len(x)):
  y1_fit.append(k1 * x[i])

coeffs,_ = curve_fit(mapping, x, y2)
k2 = coeffs
y2_fit = []
for i in range(len(x)):
  y2_fit.append(k2 * x[i])

plt.plot(x, y2, 'r^', label='Частота от номера гармоники реальная')
plt.plot(x, y2_fit, color = 'm', label = f"3: Реальная прямая(с аппроксимацией)  " r'' f", u = {k2[0]:.3f}")

plt.plot(x, y1_fit, color = '0', label=f"Расчетный(идеальный) график u = {k1[0]:.3f}", linestyle='dashed')
#--------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------
x = []
y1 = []
y2 = []

file = open('C://users/User/Documents/Mipt/labs/1.4.5/4.txt', 'r')
while (line := file.readline()):
  s = line.split()
  if (len(s) != 0):
    x.append(float(s[0].replace(',','.')))
    y1.append(float(s[1].replace(',','.')))
    y2.append(float(s[2].replace(',','.')))

k1 = 0
k2 = 0

coeffs,_ = curve_fit(mapping, x, y1)
k1 = coeffs
y1_fit = []
for i in range(len(x)):
  y1_fit.append(k1 * x[i])

coeffs,_ = curve_fit(mapping, x, y2)
k2 = coeffs
y2_fit = []
for i in range(len(x)):
  y2_fit.append(k2 * x[i])

plt.plot(x, y2, 'r^', label='Частота от номера гармоники реальная')
plt.plot(x, y2_fit, color = 'g', label = f"4: Реальная прямая(с аппроксимацией)  " r'' f", u = {k2[0]:.3f}")
plt.plot(x, y1_fit, color = '0', label=f"Расчетный(идеальный) график u = {k1[0]:.3f} ", linestyle='dashed')
#--------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------
x = []
y1 = []
y2 = []

file = open('C://users/User/Documents/Mipt/labs/1.4.5/5.txt', 'r')
while (line := file.readline()):
  s = line.split()
  if (len(s) != 0):
    x.append(float(s[0].replace(',','.')))
    y1.append(float(s[1].replace(',','.')))
    y2.append(float(s[2].replace(',','.')))

k1 = 0
k2 = 0

coeffs,_ = curve_fit(mapping, x, y1)
k1 = coeffs
y1_fit = []
for i in range(len(x)):
  y1_fit.append(k1 * x[i])

coeffs,_ = curve_fit(mapping, x, y2)
k2 = coeffs
y2_fit = []
for i in range(len(x)):
  y2_fit.append(k2 * x[i])

plt.plot(x, y2, 'r^', label='Частота от номера гармоники реальная')
plt.plot(x, y2_fit, color = 'b', label = f"5: Реальная прямая(с аппроксимацией)  " r'' f", u = {k2[0]:.3f}")

plt.plot(x, y1_fit, color = '0', label=f"Расчетный(идеальный) график u = {k1[0]:.3f}", linestyle='dashed')
#--------------------------------------------------------------------------------------------

x = []
y1 = []
y2 = []

file = open('C://users/User/Documents/Mipt/labs/1.4.5/6.txt', 'r')
while (line := file.readline()):
  s = line.split()
  if (len(s) != 0):
    x.append(float(s[0].replace(',','.')))
    y1.append(float(s[1].replace(',','.')))
    y2.append(float(s[2].replace(',','.')))

k1 = 0
k2 = 0

coeffs,_ = curve_fit(mapping, x, y1)
k1 = coeffs
y1_fit = []
for i in range(len(x)):
  y1_fit.append(k1 * x[i])

coeffs,_ = curve_fit(mapping, x, y2)
k2 = coeffs
y2_fit = []
for i in range(len(x)):
  y2_fit.append(k2 * x[i])

plt.plot(x, y2, 'r^', label='Частота от номера гармоники реальная')
plt.plot(x, y2_fit, color = 'c', label = f"2: Реальная прямая(с аппроксимацией) " r'' f", u = {k2[0]:.3f}")

plt.plot(x, y1_fit, color = '0', label= f"Расчетный(идеальный) график u = {k1[0]:.3f}", linestyle='dashed')


plt.grid(visible = True, which='major', axis='both', alpha=1)
plt.grid(visible = True, which='minor', axis='both', alpha=1)
plt.legend()
plt.show()
plt.savefig('C://users/User/Documents/Mipt/labs/1.4.5/graphic.png')
file.close()