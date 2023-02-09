/*---------------------------------------------------------------------------*\
 \============ \============             
 \|||||||||||   \|||\\\\\\\\|           //|\\
 \|||     |||   \|||                   ///|\\\
 \|||     |||   \|||                  ///###\\\
 \|||           \|||\\\\\\\\|        ///     \\\
 \|||           \|||--------|       ///#######\\\
 /|||   \\\\|   /|||////////|      //////||\\\\\\\
 /|||   //|||   /|||              ///////||\\\\\\\\
 /|||     |||   /|||             /////         \\\\\
 /|||||||||||   /|||////////|   /////           \\\\\
 /==========|   /===========|  /////             \\\\\
-------------------------------------------------------------------------------
License
    This file is part of GEA

Application
    EFgrad

Description
    Transient solver to filter the compressible Navier-Stokes equations
    with the gradient-type filter

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
        "Transient solver for filtering"
	"the compressible navier-stokes"
	"equations with the gradient-type filter"
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
	 #include "printViscosity.H" 
	 #include "RelaxationStep.H"

	 thermo.correct();

        theta = thermo.T() - gh/thermo.Cp() - theta0;

        runTime.write();
	
        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
