import serial, string
import serial.tools.list_ports

print("module ser02.py: list_ports(), open_port(\"COMx\"), r(addr), w(addr, value), close_ports()")

def list_ports(): 
	port_list = list(serial.tools.list_ports.comports())
	#print(port_list)
	if len(port_list) == 0:
		print('No serial port found.')
	else:
		for i in range(0,len(port_list)):
			print(port_list[i])
		
def esc():
	for i in range(3):
		result=ser.write(b'\x1B')
		ret = rev()
	return
	
def open_port(portx):		
	try:
		bps=115200
		timex=5
		global ser
		ser=serial.Serial(portx,bps,timeout=timex)
		print ("Open serial port at: "+portx)
	except Exception as e:
		print("Failed to open serial port: "+portx,e)
	esc()

def rev():
	r = ""
	while True:
		if ser.in_waiting:
			str=ser.read(ser.in_waiting )
			str=str.decode("windows-1252")
			if str[-1]==">":
				#print("rev:",str)
				r = r+str
				break
			else:
				#print("rev1:",str)
				r = r+str
	#print (r)                
	return r
	
def r(addr):
	addr = '%#06x'%addr
	addr = addr[2:6]
	sercom = "r "+addr+"\r\n"
	#print(sercom)
	result=ser.write(str.encode(sercom))
	ret = rev()
	#print("long: "+ret)
	ret = ret[8:12]
	#print("read value: 0x"+ret)
	a = int(ret, 16)
	#print ("0x%04x"%a, type(a))
	return a
	

    
def w(addr, value):
	addr = '%#06x'%addr
	addr = addr[2:6]
	v = '%#06x'%value
	v = v[2:6]
	sercom = "w "+addr+" "+v+"\r\n"
	#print (sercom)
	result=ser.write(str.encode(sercom))
	rev()

def close_port():
	try:
		ser.close()
		return ("Now close port at: "+ser.name)
	except Exceptioin as e:
		return ("Failed to close serial port: "+ser.name, e)

def rev_anything(r):
	i = 1000
	while i > 0:
		if ser.in_waiting:
			str=ser.read(ser.in_waiting ).decode("windows-1252")
			#print("rev:",str)
			print (str)
			i = i + 1
	return r
