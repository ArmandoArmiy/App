#Importaciones
import streamlit as st
import serial
import time
import datetime
import pandas as pd

#Dataframe's
data_tv = {
        'Consumo eléctrico (kWh)': [4, 5, 6, 4, 3, 2, 7, 6, 5, 5, 4, 
                                    5, 4, 3, 2, 6, 7, 5, 4, 3, 3, 5,
                                    6, 5, 4, 5, 6, 7, 8]
        }
df_tv = pd.DataFrame(data_tv)
data_bombilla = {
        'Consumo eléctrico (kWh)': [0.523876, 0.498249, 0.458616, 0.417582, 0.481003, 
                                    0.411030, 0.585214, 0.590826, 0.438189, 0.572357,
                                    0.515065, 0.570944, 0.455944, 0.484259, 0.503918,
                                    0.454425, 0.424107, 0.516290, 0.569167, 0.454986,
                                    0.475702, 0.424511, 0.490239, 0.390599, 0.548432,
                                    0.546306, 0.452738, 0.501411, 0.459435]
        }
df_bombilla = pd.DataFrame(data_bombilla)
data_refri = {
        'Consumo eléctrico (kWh)': [96, 80, 128, 83, 91, 86, 126, 92, 111, 107, 104, 
                                    83, 75, 99, 91, 130, 103, 88, 120, 76, 120, 98, 
                                    137, 112, 83, 109, 100, 126, 97]
        }
df_refri = pd.DataFrame(data_refri)
data_bomba = {
        'Consumo eléctrico (kWh)': [3.114254, 3.384625, 3.542337, 3.503009, 3.344850, 
                                    3.743617, 3.098995, 3.850024, 3.033305, 3.172137, 
                                    3.177282, 3.753665, 3.850509, 3.403826, 3.996985, 
                                    3.727678, 3.055344, 3.017072, 3.068743, 3.630414, 
                                    3.948541, 3.930367, 3.409604, 3.871845, 3.986707, 
                                    3.845888, 3.376538, 3.910071, 3.180810]
        }
df_bomba = pd.DataFrame(data_bomba)

#Funcion para los encabezados
def encabezados():
    st.header("Hogar")
    st.write("-------------------------------------------------------------------")
    st.subheader("Dispositivos Conectados")

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
    with col3:
        st.image('./img/refrigerador.png', use_column_width=True)
        st.caption("Refrigerador")
        if st.button("Encender",key="refri1"):
            ser = serial.Serial("COM3", 9600)
            ser.write(b'5\n')
            ser.close()
        if st.button("Apagar",key="refri0"):
            ser = serial.Serial("COM3", 9600)
            ser.write(b'6\n')
            ser.close()
    with col4:
        st.image('./img/bomba.png', use_column_width=True)
        st.caption("Bomba de agua")
        if st.button("Encender",key="bomba1"):
            ser = serial.Serial("COM3", 9600)
            ser.write(b'7\n')
            ser.close()
        if st.button("Apagar",key="bomba0"):
            ser = serial.Serial("COM3", 9600)
            ser.write(b'8\n')
            ser.close()

elif selected_tab == 'Consumo':
    encabezados()
    col1, col2, col3, col4 = st.columns(4)

    with col1:
        st.image('./img/tv.png', use_column_width=True)
        st.caption("Tv Smart")
        st.write(8,'Kwh')
    with col2:
        st.image('./img/bombilla.png', use_column_width=True)
        st.caption("Bombillas")
        st.write(3,'Kwh')
    with col3:
        st.image('./img/refrigerador.png', use_column_width=True)
        st.caption("Refrigerador")
        st.write(137,'Kwh')
    with col4:
        st.image('./img/bomba.png', use_column_width=True)
        st.caption("Bomba de agua")
        st.write(4,'Kwh')            

elif selected_tab == 'Historial':
    st.caption('Cosumo de "Tv Smart"')
    st.line_chart(df_tv,)
    st.caption('Cosumo de "Bombilla"')
    st.line_chart(df_bombilla)
    st.caption('Cosumo de "Refrigerador"')
    st.line_chart(df_refri)
    st.caption('Cosumo de "Bomba de agua"')
    st.line_chart(df_bomba)   