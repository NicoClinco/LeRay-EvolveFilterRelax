scalar AvgViscosity = 0.0;
scalar vol = gSum(U.mesh().V());
AvgViscosity = (fvc::domainIntegrate(FilterViscosityStep()).value())/runTime.deltaT().value();
AvgViscosity = AvgViscosity/vol;

std::ofstream AVfile;
AVfile.open ("ArtificialViscosity.txt", std::ofstream::out | std::ofstream::app);
AVfile << runTime.timeName() << "\t" << AvgViscosity << std::endl;

