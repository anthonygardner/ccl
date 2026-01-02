try:
    from ._mylib import hello
    
except ImportError as e:
    raise ImportError(f"Failed to import plant: {e}")
