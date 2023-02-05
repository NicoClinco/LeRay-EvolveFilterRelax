// Relax the equations :
scalar Chi = FilteringProperties.lookupOrDefault("Urelax",0.0);
scalar  Xi = FilteringProperties.lookupOrDefault("herelax",0.0);

Chi = Chi/(max(aU.ref()).value());
Xi = Xi/(max(aU.ref()).value());

UTilda = Chi*UTilda + (1-Chi)*U;

heTilda = (Xi)*heTilda + (1-Xi)*thermo.he();
