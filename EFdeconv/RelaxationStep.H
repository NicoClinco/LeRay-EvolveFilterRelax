// Relax the equations :

scalar Chi = 0.95;
scalar Xi = 0.95;

UTilda = (1-Chi)*UTilda + Chi*U;

heTilda = (1-Xi)*heTilda + Xi*thermo.he();
