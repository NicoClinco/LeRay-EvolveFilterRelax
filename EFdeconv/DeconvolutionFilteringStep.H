aU.ref() = 1.0;

aU.boundaryFieldRef() = scalar(1.0);

tmp<volScalarField> FilterViscosityStep =a.FilteringViscosityU();
 /*------------------------------------------------ First Step : LINEAR IF ----------------------------------------*/ 
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

 UTilda = Ufi;
 heTilda = hefi;
 /* -------------------------------------------------------------------------------------------------------------------- */ 

 /* /---------------------------------------------------Solve the laplacian-again--------------------------------------- \ */
 FilterViscosityStep.ref() = a.FilteringViscosityU();
 
 solve ( UfilteredEqn ==UTilda +fvm::laplacian(FilterViscosityStep(),Ufi)  ); 
 UTilda = Ufi;
 
 solve ( hefilteredEqn == heTilda + fvm::laplacian(FilterViscosityStep(),hefi) );
 heTilda = hefi;

/*   ----------------------------------------------------------------------------------------------------------------------- */ 
