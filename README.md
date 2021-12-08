# Heat Equation Solver

Heat equation 1D solver using Bender-Schmidt finite difference method (FDM).  
Basicaly heat equation principle extends wave equation.  

## Requirements
* gcc
* gnuplot

## Equations
Heat equation can be solved using partial differential equation described as below

**(∂u/∂t) = α²(∂²u/∂x²)**

Considering 
* **u** as time space vector assimilated to U 2D matrix u(x,t)
* **t** as time
* **x** as energy
* **α²** as thermal coefficient

### Alpha square
α² is the thermal coefficient represented as below

**α² = k/pc**

Considering  

* **k** as thermal conductivity (W/(m·K))
* **p** as material density (Kg/m³)
* **c** specific heat capacity (kJ. kg-¹. K-¹)

## Use case

Example providing paramaters as below
* u(x) = 150
* u(t) = 100
* α² = 4 (thermal coefficient)
* u0 = 0 (initial boundary condition)
* un = 0 (terminal boundary condition)
* h = 1 (x stepsize along x-axis)
* k = 1/8 (t stepsize along y-axis)
* Energy e(x) = 20*sin(x)+80

*Energy convolution*

![Energy](doc/assets/e.png)

*Running build script './build_heateq.sh' will show representation as below*

![heateq](doc/assets/u.png)

*Matrix U datas can be found after built [here](./heateq.dat)*

## Appendices

### Materials specific heat capacities

|Material|Heat Capacity|  
|--------|-------------|  
|Aluminium|0. 897|  
|Brass|0. 377|
|Bronze|0. 343|
|Cadmium|0. 235|
|Constantan|0. 410|
|Copper|0. 384|
|Ethanol|2. 940|
|Glass|0. 670|
|flint|0. 503|
|Pyrex|0. 753|
|Gold|0. 129|
|Graphite|0. 838|
|Ice|2. 100|
|Ironcast|0. 420|
|Kerosene|2. 100|
|Lead|0. 130|
|Magnesia|0. 930|
|Magnesium|1. 030|
|Mercury|0. 138|
|Molybdenum|0. 272|
|Nickel|0. 457|
|Oilmachine|1. 676|
|Paraffin|2. 100|
|Paraffinwax|2. 140|
|Petroleum|2. 140|
|Phosphorus|0. 796|
|Platinum|0. 133|
|Rubber|2. 010|
|Salt|0. 880|
|Sand|0. 796|
|Seawater|3. 940|
|Silica|0. 800|
|Silicon|0. 737|
|Silver|0. 236|
|Tin|0. 220|
|Titanium|0. 523|
|Tungsten|0. 142|
|Turpentine|1. 760|
|Uranium|0. 116|
|Vanadium|0. 482|
|Water|4. 196|
|Waterheavy|4. 221|
|Wood|2. 0|
|Zinc|0. 388|
