#!/usr/bin/env python
# coding: utf-8

# In[64]:


import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


# In[65]:


data = pd.read_csv("data_primer-medicion.csv")


# In[66]:


# Definimos las listas con V1 (Volumen de HCl para que el NaOH con fenolftaleína pase de rosa a transparente)\n",
V1_1 = np.array(data["#1"])[::2]
V1_2 = np.array(data["#2"])[::2]
V1_3 = np.array(data["#3"])[::2]
V1_4 = np.array(data["#4"])[::2]
                       
# Definimos las listas con V2 (Volumen agregado de HCl para que el NaOH con fenolftaleína y naranja de metilo pase de naranja a rojo)\n",
V2_1 = np.array(data["#1"])[1::2]
V2_2 = np.array(data["#2"])[1::2]
V2_3 = np.array(data["#3"])[1::2]
V2_4 = np.array(data["#4"])[1::2]


# In[67]:


# Calculamos las diferencias de volumen que representan al CO2 atrapado en el NaOH\n",
DV_1 = V2_1 - V1_1 
DV_2 = V2_2 - V1_2
DV_3 = V2_3 - V1_3
DV_4 = V2_4 - V1_4


# In[68]:


#Le restamos el primer valor, dado que el NaOH ya estaba siendo usado\n",
DV_1 = DV_1 - DV_1[0]
DV_2 = DV_2 - DV_2[0]
DV_3 = DV_3 - DV_3[0]
DV_4 = DV_4 - DV_4[0]


# In[69]:


#agrego un 0 como primer valor
#DV_1 = np.insert(DV_1, 0, 0., axis=0) 
#DV_2 = np.insert(DV_2, 0, 0., axis=0)
#DV_3 = np.insert(DV_3, 0, 0., axis=0)
#DV_4 = np.insert(DV_4, 0, 0., axis=0)


# In[70]:


DV_1


# In[71]:


x=np.array([0,1,2,3,5,6,7])


# In[76]:


plt.plot(x,DV_1,'o--',label='Almidón')
plt.plot(x,DV_2,'o--',label='Celulosa')
plt.plot(x,DV_3,'o--',label='Almidón+NP')
plt.plot(x,DV_4,'o--',label='Blanco')
plt.legend()
plt.grid(True)
plt.xlabel('Días')
plt.ylabel('Volumen [mL]')
plt.show()


# In[73]:


def gramos(x):#meter el volumen de la diferencia
    return x*0.4545*0.5*44/5
    


# In[75]:


plt.plot(x,gramos(DV_1),'o--',label='Almidón')
plt.plot(x,gramos(DV_2),'o--',label='Celulosa')
plt.plot(x,gramos(DV_3),'o--',label='Almidón+NP')
plt.plot(x,gramos(DV_4),'o--',label='Blanco')
plt.legend()
plt.grid(True)
plt.xlabel('Días')
plt.ylabel('Masa [g]')
plt.savefig('primer_medicion.png')
plt.show()


# In[ ]:




