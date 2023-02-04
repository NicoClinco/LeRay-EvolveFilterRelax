
 /* ------------------    Filter Step for Velocity --------------------------- */ 

volScalarField::Internal SqrAbsGradU =((fvc::grad(U)) && (fvc::grad(U)));
volScalarField::Internal AbsGradU = sqrt(SqrAbsGradU);

dimensionedScalar AbsGradULinf = max(AbsGradU);
dimensionedScalar one("one",AbsGradULinf.dimensions(),1.0);

dimensionedScalar NormalizingFactor = max(one,AbsGradULinf);

aU.ref()  = AbsGradU/NormalizingFactor; 

// Set the boundary field to zero in order to avoid spurious oscillations // 

forAll(aU.boundaryField(),patchi)
{
  aU.boundaryFieldRef()[patchi] = scalar(0.0);
}

tmp<volScalarField> FilterViscosityStep =a.FilteringViscosityU();

fvVectorMatrix UfilteredEqn
(
 -fvm::laplacian(FilterViscosityStep(),Ufi)-fvc::div(FilterViscosityStep()*(dev2(T(fvc::grad(U)))))
);

solve( UfilteredEqn == U-fvm::Sp(dimensionedScalar("one",dimless,1),Ufi) );
U=Ufi;

/* ------------------------ End filter Step for Velocity  ------------------------- */ 



/* ------------------------     Filter Step for Energy    --------------------------- */

volScalarField& he = thermo.he();

fvScalarMatrix hefilteredEqn
(
 fvm::Sp(dimensionedScalar("one",dimless,1),hefi)-fvm::laplacian(FilterViscosityStep(),hefi)
);

solve ( hefilteredEqn == he );
he = hefi;

thermo.correct();

/* ----------------------     End Filter Step for Energy ----------------------------- */

