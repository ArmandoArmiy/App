#Importaciones
import streamlit as st
import serial
import time
import datetime
import pandas as pd

#Funcion para los encabezados
def encabezados():
    st.header("Hogar")
    st.write("-------------------------------------------------------------------")
    st.subheader("Dispositivos Conectados")

#Funcion para obtener la temperatura
def temperature():
    linea = puerto_serial.readline().decode('utf-8').strip()
    
    ser = serial.Serial("COM3", 9600)
    ser.readlines().readline().decode('utf-8').strip
    ser.close()
    st.write(f'Dato recibido: {linea}')

#Titiulo
st.title("IntelligentEnergy")

 
# Crear opciones de pestañas
tabs = ['Dispositivos conectados','Consumo','Historial']

# Mostrar selector de pestañas en la barra lateral
with st.sidebar.container():
    # Agregar una imagen dentro del contenedor
    st.image('./img/Logo_Transp.png', width=200)

selected_tab = st.sidebar.radio('Selecciona un apartado', tabs)

# Dependiendo de la pestaña seleccionada, mostrar su contenido
if selected_tab == 'Dispositivos conectados':
    #Generaciondel encanbezado en la vista
    encabezados()
    #Creacion de columnas para alamacenar las cards de cada elemento
    col1, col2, col3, col4 = st.columns(4)
    #Cards de dispositivo
    with col1:
        #Imagen de refercia + encabezado
        st.image('./img/tv.png', use_column_width=True)
        st.caption("Tv Smart")
        #logoca para el boton, y calculo de el tiempo encendido
        if st.button("Encender",key="tv1"):
            hora_on = time.localtime()
            ser = serial.Serial("COM3", 9600)
            ser.write(b'1\n')
            ser.close()
        if st.button("Apagar",key="tv0"):
            hora_off = time.localtime()
            ser = serial.Serial("COM3", 9600)
            ser.write(b'2\n')
            ser.close()
            
    with col2:
        st.image('./img/bombilla.png', use_column_width=True)
        st.caption("Bombillas")
        if st.button("Encender",key="luz1"):
            ser = serial.Serial("COM3", 9600)
            ser.write(b'3\n')
            ser.close()
        if st.button("Apagar",key="luz0"):
            ser = serial.Serial("COM3", 9600)
            ser.write(b'4\n')
            ser.close()

elif selected_tab == 'Consumo':
    encabezados()
    col1, col2= st.columns(2)

    with col1:
        st.image('./img/tv.png', use_column_width=True)
        st.caption("Tv Smart")
        st.write(8,'Kwh')
    with col2:
        st.image('./img/bombilla.png', use_column_width=True)
        st.caption("Bombillas")
        st.write(3,'Kwh')           