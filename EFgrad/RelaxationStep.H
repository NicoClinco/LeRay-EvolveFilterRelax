// Relax the equations :
scalar Chi = FilteringProperties.lookupOrDefault("Urelax",0.0);
scalar  Xi = FilteringProperties.lookupOrDefault("herelax",0.0);

//Chi = Chi/(max(aU.ref()).value());
//Xi = Xi/(max(aU.ref()).value());


U = Chi*Ufi + (1-Chi)*U;

thermo.he() = (Xi)*hefi + (1-Xi)*thermo.he();


