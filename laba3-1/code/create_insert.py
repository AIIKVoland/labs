import sqlite3
import serial
import datetime
import csv

# Создаем подключение к базе данных (файл ValueDB будет создан)
connection = sqlite3.connect('lab_3.1/data/ValueDB.db')
cursor = connection.cursor()

def create_db():
    # Создаем таблицу Users
    sql = '''
    CREATE TABLE IF NOT EXISTS HC_SR501 (
    id INTEGER PRIMARY KEY,
    value TEXT,
    log_time timestamp
    );
    '''
    cursor.execute(sql)
    
    print("Table created")

    # Сохраняем изменения
    connection.commit()

def insert_data(id, value, log_time):
    # Добавляем нововы данные датчика
    cursor.execute('INSERT INTO HC_SR501 (id, value, log_time) VALUES (?, ?, ?);', (id, value, log_time))
    print("data insert")
    connection.commit()

def main():
    create_db()
    i = 1
    
    # open the file in the write mode
    f = open('lab_3.1/data/values.csv', 'w')
    
    print("CSV created")
    # create the csv writer
    writer = csv.writer(f)
    
    #Для считывания с ардуино
    ser = serial.Serial('/dev/cu.usbmodem11101', 9600)
    print("serial connected")
    
    while i<10:
        # Считываем значения с датчика движения
        pirVal = ser.readline().decode('utf-8').rstrip()
        insert_data(i, pirVal, datetime.datetime.now())
        
        # Если обнаружили движение, то выводим сообщение о тревоге
        if pirVal == "HIGH":
            print("Тревога")
        else:
            print("Сканирую")
        
        ser.flushInput()
        
        # write a row to the csv file
        writer.writerow((i, pirVal, datetime.datetime.now()))
        # close the file
        f.flush()
        i += 1
    
    #закрываем соединение с БД
    connection.close()
    #закрываем файл
    f.close()
    #закрываем порт
    ser.close()


if __name__ == '__main__':
    main()