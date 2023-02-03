/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2022 AUTHOR,AFFILIATION
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    CheckCoord

Description

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
class IndicatorFunction
{
 protected:

 dimensionedScalar& alphaRadius_; //Radius in which we're interested
 
  volScalarField& a_U; //Indicator Function for U 
  volScalarField& a_E; //Indicator Function for Temperature
 
  public:

  IndicatorFunction() =delete;

  IndicatorFunction(const IndicatorFunction&) = delete;

  IndicatorFunction(dimensionedScalar& _alphar,volScalarField& _aU,volScalarField& _aE);

  dimensionedScalar&  alphaRadiusRef();

  const dimensionedScalar& alphaRadius() const;
  
   tmp<volScalarField> FilteringViscosityU() const;
  
   tmp<volScalarField> FilteringViscosityE() const;

  const volScalarField& aU() const;

  const volScalarField& aE() const;
  
  ~IndicatorFunction();
  
  friend  Ostream& operator<< (Ostream&,const IndicatorFunction&);
};

// ************************************************************************* //
