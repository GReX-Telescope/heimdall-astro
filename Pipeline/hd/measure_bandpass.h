
#pragma once

#include "hd/error.h"
#include "hd/types.h"

hd_error measure_bandpass(const hd_byte* d_in,
                          hd_size        nsamps,
                          hd_size        nchans,
                          hd_size        nbits,
                          hd_float*      d_bandpass,
                          hd_float*      rms);

// Note: This returns an estimate from a sub-sample, not the exact average
hd_error measure_band_avg(const hd_byte* d_filterbank,
                          hd_size        nsamps,
                          hd_size        nchans,
                          hd_size        nbits,
                          hd_float*      d_band_avg);
/*
hd_error measure_band_outliers(const hd_byte* d_filterbank,
                               hd_size        nsamps,
                               hd_size        nchans,
                               hd_size        nbits,
                               hd_float       thresh,
                               hd_float*      d_band_outlier_fracs);
*/
