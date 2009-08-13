/** \file apop_uniform.c 

Copyright (c) 2007 by Ben Klemens.  Licensed under the modified GNU GPL v2; see COPYING and COPYING2.  */

#include "model.h"
#include "likelihoods.h"

apop_model apop_uniform;

static apop_model * uniform_estimate(apop_data * data,  apop_model *parameters){
  apop_model 	*est= parameters ? parameters : apop_model_copy(apop_uniform);
  apop_model_clear(data, est);
    est->parameters->vector->data[0]    = gsl_matrix_min(data->matrix);
    est->parameters->vector->data[1]    = gsl_matrix_max(data->matrix);
    return est;
}


static double unif_ll(apop_data *d, apop_model *m){
  apop_assert(m->parameters,  0, 0,'s', "You asked me to evaluate an un-parametrized model.");
    if (gsl_matrix_min(d->matrix)> m->parameters->vector->data[0] 
            && gsl_matrix_max(d->matrix)< m->parameters->vector->data[1])
        return log(m->parameters->vector->data[1] - m->parameters->vector->data[0]) * d->matrix->size1 * d->matrix->size2;
    return GSL_NEGINF;
}

static double unif_p(apop_data *d, apop_model *m){
  apop_assert(m->parameters,  0, 0,'s', "You asked me to evaluate an un-parametrized model.");
    if (gsl_matrix_min(d->matrix)> m->parameters->vector->data[0] 
            && gsl_matrix_max(d->matrix)< m->parameters->vector->data[1])
        return pow(m->parameters->vector->data[1] - m->parameters->vector->data[0],  
                            d->matrix->size1 * d->matrix->size2);
    return 0;
}

static void uniform_rng(double *out, gsl_rng *r, apop_model* eps){
    *out =  gsl_rng_uniform(r) *(eps->parameters->vector->data[1]- eps->parameters->vector->data[0])+ eps->parameters->vector->data[0];
}

/** The uniform model.
This is the two-parameter version of the uniform, expressing a uniform distribution over [a, b].

The MLE of this distribution is simply a = min(your data); b = max(your data).
Primarily useful for the RNG, such as when you have a Uniform prior model.

\hideinitializer
\ingroup models
*/
apop_model apop_uniform = {"Uniform distribution", 2, 0, 0,  
    .estimate = uniform_estimate,  .p = unif_p,.log_likelihood = unif_ll,  .draw = uniform_rng};


static apop_model * improper_uniform_estimate(apop_data * data,  apop_model *parameters){
    return parameters;
}

static double improper_unif_ll(apop_data *d, apop_model *m){ return 0; }

static double improper_unif_p(apop_data *d, apop_model *m){ return 1; }

static void improper_uniform_rng(double *out, gsl_rng *r, apop_model* eps){
    apop_assert_void(0, 0, 's', "It doesn't make sense to make random draws from an improper Uniform.");
}

/** The improper uniform returns P(x) = 1 for every value of x, all the
time (and thus, log likelihood(x)=0).  It has zero parameters. It is
useful, for example, as an input to Bayesian updating, to represent a
fully neutral prior.

The \c estimate routine is just a dummy that returns its input.

The \c draw function makes no sense, and therefore returns an error.

\hideinitializer
\ingroup models
*/
apop_model apop_improper_uniform = {"Uniform distribution", 2, 0, 0,  
    .estimate = improper_uniform_estimate,  .p = improper_unif_p,.log_likelihood = improper_unif_ll,  .draw = improper_uniform_rng};

