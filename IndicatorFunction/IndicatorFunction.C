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
*/

// Class implementation

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


// ************************************************************************* //
