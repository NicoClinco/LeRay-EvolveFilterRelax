
/* // ------------------- Filtering the velocity ------------------------- \\   */

tmp<volScalarField> FilterViscosityStep =a.FilteringViscosityU();

fvVectorMatrix UfilteredEqn
(
 -fvm::laplacian(FilterViscosityStep(),Ufi)
);

solve( UfilteredEqn == U-fvm::Sp(dimensionedScalar("one",dimless,1),Ufi) );
U=Ufi;

/* // --------------------------------------------------------------------- \\  */


/* // ------------------- Filtering the Energy ----------------------------- \\ */


FilterViscosityStep = a.FilteringViscosityE();

volScalarField& he = thermo.he();

fvScalarMatrix hefilteredEqn
(
 fvm::Sp(dimensionedScalar("one",dimless,1),hefi)-fvm::laplacian(FilterViscosityStep(),hefi)
);

solve ( hefilteredEqn == he );
he = hefi;

thermo.correct();

/* // ------------------------------------------------------------------------ \\ */ 
