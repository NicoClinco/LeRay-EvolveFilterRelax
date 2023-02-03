/*---------------------------------------------------------------------------*\
 
License
    This file is part of GEA
    GEA is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    GEA is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.
    You should have received a copy of the GNU Lesser General Public License
    along with ITHACA-FV. If not, see <http://www.gnu.org/licenses/>.
Application
    dryAir
Description
    Transient solver for compressible Navier-Stokes equations with gravity
    Turbulence is modelled using the linear-filter 
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "rhoThermo.H"
#include "turbulentFluidThermoModel.H"
#include "fvOptions.H"
#include "pimpleControl.H"
#include "pointMesh.H"
#include "interpolation.H"
#include "volPointInterpolation.H"
#include "primitivePatchInterpolation.H"
#include "IndicatorFunction.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Transient solver for dryAir, with the"
	 " linear filter approach"
    );

    #include "postProcess.H"
    #include "addCheckCaseOptions.H"
    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createControl.H"
    #include "createFields.H"
    #include "createFieldRefs.H"
    #include "createIndicatorFunction.H"
    #include "initContinuityErrs.H"
    #include "createTimeControls.H"
    #include "compressibleCourantNo.H" 
    #include "setInitialDeltaT.H"

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    while (runTime.run())
    {
        #include "readTimeControls.H"
        #include "compressibleCourantNo.H"
        #include "setDeltaT.H"

        ++runTime;

        Info<< "Time = " << runTime.timeName() << nl << endl;

        #include "rhoEqn.H"

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {  

            #include "UEqn.H"
            #include "EEqn.H"

            // --- Pressure corrector loop
            while (pimple.correct())
            {
                #include "pEqn.H"
            }

            if (pimple.turbCorr())
            {
                turbulence->correct();
            }
        }

        rho = thermo.rho();
        
	#include "FilteringStep.H"

        theta = thermo.T() - gh/thermo.Cp() - theta0;
         
	runTime.write();

        /*
        scalar vmax = max(U.component(1)).value();
        scalar vavg = 0;
        scalar Volume = 0;

        forAll (U.internalField(), cellI)
        {
             vavg += (U[cellI] & vector (0, 1, 0))*mesh.V()[cellI];
             Volume += mesh.V()[cellI];
        }

        reduce(vavg, sumOp<scalar> ());
        reduce(Volume, sumOp<scalar> ());

        vavg = vavg/Volume;
       
        
        std::ofstream file;
        file.open ("results.txt", std::ofstream::out | std::ofstream::app);

       if (Pstream::master())
        {
            file << runTime.timeName() << "\t" << vmax << "\t" << vavg << std::endl << "\n";
        }
        */

        
	/*
	fileName NameViscosity("ArtificialViscosity");
	OFstream fileViscous(runTime.timeName()/"ArtificialViscosity.txt");
	Info << runTime.timeName()<<endl;
	fileViscous << " Filtering viscosity Step at time "
	<<runTime.timeName() <<"endl";
	fileViscous << FilterViscosityStep() <<endl;
 	*/
	
	// Make a file in which i should put the injected viscosity 
	// at various time-step 
	
        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
