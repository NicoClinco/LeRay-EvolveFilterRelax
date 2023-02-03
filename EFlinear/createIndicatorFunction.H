dimensionedScalar alphaR("FilteringRadius",dimLength,transportProperties);

volScalarField aU
(
  IOobject
  (
    "aU",
    runTime.timeName(),
    mesh,
    IOobject::READ_IF_PRESENT,
    IOobject::AUTO_WRITE
  ),
 mesh	
);

volScalarField aE
(
 IOobject
 (
  "aE",
  runTime.timeName(),
  mesh,
  IOobject::READ_IF_PRESENT,
  IOobject::AUTO_WRITE
 ),
 mesh
);


volVectorField Ufi
(
 IOobject
 (
   "U_filtered",
   runTime.timeName(),
   mesh,
   IOobject::NO_READ,
   IOobject::AUTO_WRITE
 ),
 U
);


volScalarField hefi
(
 IOobject
 (
  "he_filtered",
  runTime.timeName(),
  mesh,
  IOobject::NO_READ,
  IOobject::AUTO_WRITE
 ),
 thermo.he()
);


IndicatorFunction a(alphaR,aU,aE);

