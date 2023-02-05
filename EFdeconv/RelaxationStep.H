// Relax the equations :
scalar Chi = FilteringProperties.lookupOrDefault("Urelax",0.0);
scalar  Xi = FilteringProperties.lookupOrDefault("herelax",0.0);

UTilda = (1-Chi)*UTilda + Chi*U;

heTilda = (1-Xi)*heTilda + Xi*thermo.he();
