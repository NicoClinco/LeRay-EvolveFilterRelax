// Relax the equations :
scalar Chi = FilteringProperties.lookupOrDefault("Urelax",1.0);
scalar  Xi = FilteringProperties.lookupOrDefault("herelax",1.0);

//Chi = Chi/(max(aU.ref()).value());
//Xi = Xi/(max(aU.ref()).value());


U = Chi*Ufi + (1-Chi)*U;

thermo.he() = (Xi)*hefi + (1-Xi)*thermo.he();


