{-
    Module with some constants and utility functions
-}
module Utils where
    
-- Third party
import System.Console.ANSI as C


-- < Logging functions > -----------------------------------
logErr :: String -> IO ()
logErr msg      = _setErrColor      >> putStrLn ("[ERROR] " ++ msg)     >> _resetColor

logWarn :: String -> IO ()
logWarn msg     = _setWarnColor     >> putStrLn ("[WARNING] " ++ msg)   >> _resetColor

logSuccess :: String -> IO ()
logSuccess msg  = _setSuccessColor  >> putStrLn ("[SUCCESS] " ++ msg)   >> _resetColor

logInfo :: String -> IO ()
logInfo msg     = _setInfoColor     >> putStrLn ("[INFO] " ++ msg)      >> _resetColor

logTrace :: String -> IO ()
logTrace msg    = _setTraceColor    >> putStrLn ("[TRACE] " ++ msg)     >> _resetColor

-- | Set terminal colors
_setErrColor :: IO()
_setErrColor = C.setSGR [C.SetColor C.Foreground C.Vivid C.Red ]

_setWarnColor :: IO()
_setWarnColor = C.setSGR [C.SetColor C.Foreground C.Vivid C.Yellow ]

_setSuccessColor :: IO()
_setSuccessColor = C.setSGR [C.SetColor C.Foreground C.Vivid C.Green ]

_setInfoColor :: IO()
_setInfoColor = C.setSGR [C.SetColor C.Foreground C.Vivid C.Blue ]

_setTraceColor :: IO()
_setTraceColor = C.setSGR [C.SetColor C.Foreground C.Vivid C.White ]

_resetColor :: IO()
_resetColor = C.setSGR [C.Reset]
