# El objetivo es calcular los rendimientos totales de todas las acciones del portafolio
# 130 , 660 , 80 , 100 , 30

cap_total = 2000

precio_compra = [130 , 660 , 80 , 100 , 30] # = 1000

precio_venta = [150 , 897.6 , 48 , 102 , 37] # = 1234.6

diferencial = sum(precio_venta) - sum(precio_compra)

#print(sum(precio_compra + precio_venta))

#esta es mi ganancia
print(diferencial.__round__())

a = diferencial.__round__() / cap_total * 100

print(f"{a}%")