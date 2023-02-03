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
// Class implementation:

Description

\*---------------------------------------------------------------------------*/

#include "IndicatorFunction.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
IndicatorFunction::IndicatorFunction(dimensionedScalar& _alphar,volScalarField& _aU,volScalarField& _aE):
	alphaRadius_(_alphar),
	a_U(_aU),
	a_E(_aE)
{
};

dimensionedScalar& IndicatorFunction::alphaRadiusRef(){
	return alphaRadius_;
}
const dimensionedScalar& IndicatorFunction::alphaRadius() const {
	return alphaRadius_;
}

tmp<volScalarField> IndicatorFunction::FilteringViscosityU() const {
	dimensionedScalar SqRadius = pow(alphaRadius_,2);	
	tmp<volScalarField> AlphaaU(SqRadius*a_U);
	return AlphaaU;
}

tmp<volScalarField> IndicatorFunction::FilteringViscosityE() const 
{
	dimensionedScalar SqRadius = pow(alphaRadius_,2);
	tmp<volScalarField> AlphaaT(SqRadius*a_E);
	return AlphaaT;
}

const volScalarField& IndicatorFunction::aU() const{
	return a_U;
}

const volScalarField& IndicatorFunction::aE() const{
	return a_E;
}

IndicatorFunction::~IndicatorFunction(){};

Ostream& operator<<(Ostream& os,const IndicatorFunction& IF)
{
  os << "Filtering Radius : "
  << IF.alphaRadius_.value() <<endl;
  os << " Indicator Function for velocity : \n "  
  << IF.a_U <<endl;
  os << "Indicator Function for temperature : \n"
  << IF.a_E<<endl;
  return os;
};


// ************************************************************************* //
