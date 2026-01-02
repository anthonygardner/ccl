import pytest

import ccl

def test_default_constructor_zero_gains():
    pid = ccl.PID()
    assert pid.kp == 0.0
    assert pid.ki == 0.0
    assert pid.kd == 0.0
    
def test_p_only_returns_kp_times_error():
    pid = ccl.PID(2.0, 0.0, 0.0)
    output = pid.update(10.0, 0.0, 0.1)
    assert output == 20.0
    
def test_output_clamped_to_min():
    pid = ccl.PID(1.0, 0.0, 0.0)
    pid.min_output = -1.5
    output = pid.update(-10.0, 0.0, 0.1)
    assert output == pid.min_output
    
def test_output_clamped_to_max():
    pid = ccl.PID(1.0, 0.0, 0.0)
    pid.max_output = 1.5
    output = pid.update(10.0, 0.0, 0.1)
    assert output == pid.max_output
    
def test_reset_clears_integral():
    pid = ccl.PID(1.0, 0.0, 0.0)
    output = pid.update(10.0, 0.0, 0.1)
    assert output > 0.0
    
    pid.reset()
    output = pid.update(0.0, 0.0, 0.1)
    assert output == 0.0