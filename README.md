# no
It is a pice of software that simulates the the differences of pressure created at the surface of an object traveling through a homogeneous environment . 
Worning this app is designed on the Direct X framework

The mathematics behind calculating and simulating such action are qite simple:
1 We find the angle between the surface and the direction vector by creating a function of the object 
  which we derivative in order to get the tangent of each point relative to the xyz axis of the object 
2 We find the speed of the object and the orientation reletiv to the surrounding space 
3 We multuply the speed , the cosine of the angle and the impact 
4 We display the result by modifying the color shaders of the object , letting the pixel to take the value of the equation 

Status:
All the rndering and positionnig calculations are done 
Things that are currently in progres 
-Inserting the math equation 
-Creating the playground map 
-Giving the user a playable character 
