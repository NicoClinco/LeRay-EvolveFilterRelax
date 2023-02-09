// Relax the equations :
scalar Chi = FilteringProperties.lookupOrDefault("Urelax",1.0);
scalar  Xi = FilteringProperties.lookupOrDefault("herelax",1.0);

UTilda = Chi*UTilda + (1-Chi)*U;

heTilda = (Xi)*heTilda + (1-Xi)*thermo.he();
