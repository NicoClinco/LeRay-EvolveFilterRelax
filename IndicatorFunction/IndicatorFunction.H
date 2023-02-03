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
    

Description
    
    General class useful to filter the compressible Navier Stokes equations:
     
     alpha_Radius_ : Filtering Radius 
     a_U           : Indicator Function for the velocity
     a_E           : Indicator Function for the Energy

    
 
\*---------------------------------------------------------------------------*/


#include "fvCFD.H"

class IndicatorFunction
{
 protected:

 dimensionedScalar& alphaRadius_; //FilteringRadius
  volScalarField& a_U; //Indicator function for the velocity
  volScalarField& a_E; //Indicator Function for the energy
 
  public:

  IndicatorFunction() =delete;

  IndicatorFunction(const IndicatorFunction&) = delete;

  IndicatorFunction(dimensionedScalar& _alphar,volScalarField& _aU,volScalarField& _aE);

  dimensionedScalar&  alphaRadiusRef();

  const dimensionedScalar& alphaRadius() const;
  
   // Filtering-viscosities:

   
   tmp<volScalarField> FilteringViscosityU() const;
  
   tmp<volScalarField> FilteringViscosityE() const;

  const volScalarField& aU() const;

  const volScalarField& aE() const;
  
  ~IndicatorFunction();
  
};

// ************************************************************************* //
