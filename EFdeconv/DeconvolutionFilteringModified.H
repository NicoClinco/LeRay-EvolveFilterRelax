aU.ref() = 1.0;
aE.ref() = 1.0;

aU.boundaryFieldRef() = scalar(1.0);
aE.boundaryFieldRef() = scalar(1.0);

tmp<volScalarField> FilterViscosityStep =a.FilteringViscosityU();
tmp<volScalarField> FilterViscosityStepHE = a.FilteringViscosityE();
 /*------------------------------------------------ First Step : LINEAR IF ----------------------------------------*/ 

// Evaluation of the linear step thanks to the viscosity evaluated by the velocity ( IT IS THE SAME FOR THE ENERGY!)
 // a(U) = 1 , \delta = radius
 
 fvVectorMatrix UfilteredEqn
 (
  fvm::Sp(dimensionedScalar("one",dimless,1),Ufi)
 );

 solve( UfilteredEqn == UTilda +fvm::laplacian(FilterViscosityStep(),Ufi) );
 

 fvScalarMatrix hefilteredEqn
 (
  fvm::Sp(dimensionedScalar("one",dimless,1),hefi)
 );

 solve( hefilteredEqn == heTilda + fvm::laplacian(FilterViscosityStep(),hefi) );

 /* ----------------------------------------------------------------------------------------------------------------- */
 
 /* ----------------------------------------------- Evaluation of the Indicator Function ----------------------------- */
 dimensionedScalar one("one",U.dimensions(),1.0);
 volVectorField::Internal deltaU = (Ufi.internalField()-UTilda.internalField());
 volScalarField::Internal Udifference = mag(deltaU);
 dimensionedScalar maxDiff = max(Udifference);
 dimensionedScalar NormalizingFactor = max( one , maxDiff );
 aU.ref() = Udifference/NormalizingFactor;                  //aU = |uFi - U(evolve)|/max(1,normInf(Ufi-U(Evolve)))

 
 forAll(aU.boundaryField(),patchi)
{
  aU.boundaryFieldRef()[patchi] = scalar(0.0);
} 

/* -------------------------------------------- Evaluation of the Indicator Function for entalphy ------------------ */

//one.dimensions() = hefi.dimensions();
//maxDiff.dimensions() = hefi.dimensions();

dimensionedScalar oneE("oneE",heTilda.dimensions(),1.0);
volScalarField::Internal deltaHE =( hefi.internalField() - heTilda.internalField());
volScalarField::Internal HEdifference = mag(deltaHE);
dimensionedScalar maxDiffE = max(HEdifference); 
dimensionedScalar NormalizingFactorE = max(oneE,maxDiffE);
aE.ref() = HEdifference/NormalizingFactorE;


 forAll(aE.boundaryField(),patchi)
{
  aE.boundaryFieldRef()[patchi] = scalar(0.0);
}

/* ------------------------------------------------------------------------------------------------------------------ */



 UTilda = Ufi;
 heTilda = hefi;
 /* -------------------------------------------------------------------------------------------------------------------- */ 
 fvVectorMatrix UfiEqn 
 ( 
  fvm::Sp(dimensionedScalar("one",dimless,1),Ufi)
 );

 fvScalarMatrix hefiEqn
 (
  fvm::Sp(dimensionedScalar("one",dimless,1),hefi)
 );

 /* /---------------------------------------------------Solve the laplacian-again--------------------------------------- \ */
 FilterViscosityStep.ref() = a.FilteringViscosityU();
 
 solve ( UfiEqn == U +fvm::laplacian(FilterViscosityStep(),Ufi)  ); 
 UTilda = Ufi;

 FilterViscosityStepHE.ref() = a.FilteringViscosityE();

 solve ( hefiEqn == thermo.he() + fvm::laplacian(FilterViscosityStepHE(),hefi) );
 heTilda = hefi;

/*   ----------------------------------------------------------------------------------------------------------------------- */ 
