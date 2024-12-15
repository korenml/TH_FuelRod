/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2012-2017 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
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

\*---------------------------------------------------------------------------*/

#include "hUO2polyThermo.H"
#include "specie.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class EquationOfState>
inline void Foam::hUO2polyThermo<EquationOfState>::checkT
(
    const scalar T
) const
{
    if (T < 0)
    {
        FatalErrorInFunction
            << "attempt to evaluate hUO2polyThermo<EquationOfState>"
               " for negative temperature " << T
            << abort(FatalError);
    }
}


template<class EquationOfState>
inline Foam::hUO2polyThermo<EquationOfState>::hUO2polyThermo
(
    const word& name,
    const hUO2polyThermo& jt
)
:
    EquationOfState(name, jt),
    Tref_(jt.Tref_),
    Hf_(jt.Hf_)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
inline Foam::hUO2polyThermo<EquationOfState>::hUO2polyThermo
(
    const EquationOfState& st,
    const scalar Tref,
    const scalar Hf
)
:
    EquationOfState(st),
    Tref_(Tref),
    Hf_(Hf)
{}


template<class EquationOfState>
inline Foam::autoPtr<Foam::hUO2polyThermo<EquationOfState>>
Foam::hUO2polyThermo<EquationOfState>::clone() const
{
    return autoPtr<hUO2polyThermo<EquationOfState>>::New(*this);
}


template<class EquationOfState>
inline Foam::autoPtr<Foam::hUO2polyThermo<EquationOfState>>
Foam::hUO2polyThermo<EquationOfState>::New(const dictionary& dict)
{
    return autoPtr<hUO2polyThermo<EquationOfState>>::New(dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
inline Foam::scalar Foam::hUO2polyThermo<EquationOfState>::limit
(
    const scalar T
) const
{
    return T;
}


template<class EquationOfState>
inline Foam::scalar Foam::hUO2polyThermo<EquationOfState>::Cp
(
    const scalar p, const scalar T
) const
{   
    //const scalar tau = T/1000;
    //const scalar MUO2 = 270.03e-3;
    
    return (193.236 + 325.708e-3*T 
    - 311.969e-6*pow(T,2) + 116.809e-9*pow(T,3) - 9.752e-12*pow(T,4));
    
    /*
    (
        		(52.1743 
        		+ 87.951*T/1000 
        		- 84.2411*pow(T/1000,2) 
        		+ 31.542*pow(T/1000,3) 
        		- 2.6334*pow(T/1000,4) 
        		)/MUO2
        + EquationOfState::Cp(p, T)
    );
    */
}


template<class EquationOfState>
inline Foam::scalar Foam::hUO2polyThermo<EquationOfState>::Ha
(
    const scalar p, const scalar T
) const
{
    return Hs(p, T) + Hc();
}


template<class EquationOfState>
inline Foam::scalar Foam::hUO2polyThermo<EquationOfState>::Hs
(
    const scalar p, const scalar T
) const
{
    //const scalar tau = T/1000;
    //const scalar tauStd = Tstd/1000;
    //const scalar MUO2 = 270.03e-3;

	return 
	/*
	(52.1743*(T/1000 - Tref_/1000) 
    		+ 87.951*(pow(T/1000,2) - pow(Tref_/1000,2))/2 
    		- 84.2411*(pow(T/1000,3) - pow(Tref_/1000,3))/3
        	+ 31.542*(pow(T/1000,4) - pow(Tref_/1000,4))/4 
        	- 2.6334*(pow(T/1000,5) - pow(Tref_/1000,5))/5 
        	)/MUO2
      + EquationOfState::H(p, T);
    */
	(193.236e-3*(T-Tstd) + 0.5*325.708e-6*(pow(T,2)-pow(Tstd,2))
	- 311.969e-9*(1.0/3.0)*(pow(T,3)-pow(Tstd,3))
	+ 116.809e-12*(1.0/4.0)*(pow(T,4)-pow(Tstd,4))
	- 9.752e-15*(1.0/5.0)*(pow(T,5)-pow(Tstd,5)));// + EquationOfState::H(p, T);
	//300*(T-Tref_) + EquationOfState::H(p, T);
	/*
    		(52.1743*(T/1000 - Tstd/1000) 
    		+ 87.951*(pow(T/1000,2) - pow(Tstd/1000,2))/2 
    		- 84.2411*(pow(T/1000,3) - pow(Tstd/1000,3))/3
        	+ 31.542*(pow(T/1000,4) - pow(Tstd/1000,4))/4 
        	- 2.6334*(pow(T/1000,5) - pow(Tstd/1000,5))/5 
        	- 0.71391*(pow(T/1000,-1) - pow(Tstd/1000,-1))
        	)/MUO2
      + EquationOfState::H(p, T);
    */
}


template<class EquationOfState>
inline Foam::scalar Foam::hUO2polyThermo<EquationOfState>::Hc() const
{
    return Hf_;
}


template<class EquationOfState>
inline Foam::scalar Foam::hUO2polyThermo<EquationOfState>::S
(
    const scalar p, const scalar T
) const
{
    
    const scalar tau = T/1000;
    const scalar tauStd = Tstd/1000;
    const scalar MUO2 = 270.03e-3;

    return 300*log(T/Tstd) + EquationOfState::S(p, T);
    /*
    	(52.1743 + 87.951*tau - 84.2411*pow(tau,2) + 31.542*pow(tau,3) - 2.6334*pow(tau,4) + 0.71391*pow(tau,-2))/MUO2
    	- (52.1743 + 87.951*tauStd - 84.2411*pow(tauStd,2) + 31.542*pow(tauStd,3) - 2.6334*pow(tauStd,4) + 0.71391*pow(tauStd,-2))/MUO2
    	+ EquationOfState::S(p, T);
    */
}


template<class EquationOfState>
inline Foam::scalar Foam::hUO2polyThermo<EquationOfState>::Gstd
(
    const scalar T
) const
{
    const scalar c0_ = 1.0;
    const scalar n0_ = 1.0;
    const scalar tau = T/1000;
    const scalar tauStd = Tstd/1000;
    const scalar MUO2 = 270.03e-3;

    return 300*(T-Tref_) + Hc() -300*T*log(T/Tstd);
    /* 
    	(52.1743*(tau-tauStd) + 87.951*(pow(tau,2)-pow(tauStd,2))/2 - 84.2411*(pow(tau,3)-pow(tauStd,3))/3
        + 31.542*(pow(tau,4)-pow(tauStd,4))/4 - 2.6334*(pow(tau,5)-pow(tauStd,5))/5 - 0.71391*(pow(tau,-1)-pow(tauStd,-1)))/MUO2
        + Hc()
        - T*((52.1743 + 87.951*tau - 84.2411*pow(tau,2) + 31.542*pow(tau,3) - 2.6334*pow(tau,4) + 0.71391*pow(tau,-2))/MUO2
    	- (52.1743 + 87.951*tauStd - 84.2411*pow(tauStd,2) + 31.542*pow(tauStd,3) - 2.6334*pow(tauStd,4) + 0.71391*pow(tauStd,-2))/MUO2);
    */
}


template<class EquationOfState>
inline Foam::scalar Foam::hUO2polyThermo<EquationOfState>::dCpdT
(
    const scalar p, const scalar T
) const
{
    // To be implemented
    NotImplemented;
    return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class EquationOfState>
inline void Foam::hUO2polyThermo<EquationOfState>::operator+=
(
    const hUO2polyThermo<EquationOfState>& ct
)
{
    scalar Y1 = this->Y();

    EquationOfState::operator+=(ct);

    if (mag(this->Y()) > SMALL)
    {
        Y1 /= this->Y();
        const scalar Y2 = ct.Y()/this->Y();

        Hf_ = Y1*Hf_ + Y2*ct.Hf_;
        Tref_ = Y1*Tref_ + Y2*ct.Tref_;
    }
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class EquationOfState>
inline Foam::hUO2polyThermo<EquationOfState> Foam::operator+
(
    const hUO2polyThermo<EquationOfState>& ct1,
    const hUO2polyThermo<EquationOfState>& ct2
)
{
    EquationOfState eofs
    (
        static_cast<const EquationOfState&>(ct1)
      + static_cast<const EquationOfState&>(ct2)
    );

    if (mag(eofs.Y()) < SMALL)
    {
        return hUO2polyThermo<EquationOfState>
        (
            eofs,
            ct1.Tref_,
            ct1.Hf_
        );
    }
    else
    {
        return hUO2polyThermo<EquationOfState>
        (
            eofs,
            ct1.Y()/eofs.Y()*ct1.Tref_
          + ct2.Y()/eofs.Y()*ct2.Tref_,
            ct1.Y()/eofs.Y()*ct1.Hf_
          + ct2.Y()/eofs.Y()*ct2.Hf_
        );
    }
}


template<class EquationOfState>
inline Foam::hUO2polyThermo<EquationOfState> Foam::operator*
(
    const scalar s,
    const hUO2polyThermo<EquationOfState>& ct
)
{
    return hUO2polyThermo<EquationOfState>
    (
        s*static_cast<const EquationOfState&>(ct),
        ct.Tref_,
        ct.Hf_
    );
}


template<class EquationOfState>
inline Foam::hUO2polyThermo<EquationOfState> Foam::operator==
(
    const hUO2polyThermo<EquationOfState>& ct1,
    const hUO2polyThermo<EquationOfState>& ct2
)
{
    EquationOfState eofs
    (
        static_cast<const EquationOfState&>(ct1)
     == static_cast<const EquationOfState&>(ct2)
    );

    return hUO2polyThermo<EquationOfState>
    (
        eofs,
        ct2.Y()/eofs.Y()*ct2.Tref_
      - ct1.Y()/eofs.Y()*ct1.Tref_,
        ct2.Y()/eofs.Y()*ct2.Hf_
      - ct1.Y()/eofs.Y()*ct1.Hf_
    );
}


// ************************************************************************* //
