
/*Velocity*/

 //  Modello alla Smagorinsky  

volScalarField::Internal SqrAbsGradU =((fvc::grad(U)) && (fvc::grad(U)));
volScalarField::Internal AbsGradU = sqrt(SqrAbsGradU);

dimensionedScalar AbsGradULinf = max(AbsGradU);
dimensionedScalar one("one",AbsGradULinf.dimensions(),1.0);

dimensionedScalar NormalizingFactor = max(one,AbsGradULinf);

aU.ref()  = AbsGradU/NormalizingFactor; 

// Set di 0 al boundary prima prova

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



/* Energy*/

//FilterViscosityStep = a.FilteringViscosityE();
volScalarField& he = thermo.he();

// Parte che tratto in implicito

//fvScalarMatrix hefilteredEqn(hefi,thermo.he().dimensions());

//hefilteredEqn-= fvm::laplacian(FilterViscosityStep(),hefi);

fvScalarMatrix hefilteredEqn
(
 fvm::Sp(dimensionedScalar("one",dimless,1),hefi)-fvm::laplacian(FilterViscosityStep(),hefi)
);


solve ( hefilteredEqn == he );
he = hefi;

thermo.correct();

//he = he + fvc::laplacian(FilterViscosityStep(),he);

//volScalarField& Temp = thermo.T();

//Temp = Temp + fvc::laplacian(FilterViscosityStep(),Temp);

