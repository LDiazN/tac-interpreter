{-# OPTIONS_GHC -Wall #-}
module Lib
    ( taci
    ) where

import System.Directory ( doesFileExist )
import System.Console.ANSI as C
import Data.List(isSuffixOf)
import Control.Monad(unless)

-- Main function. Execute app with a given set of command line arguments, including the command name
taci :: [String] -> IO()
taci args 
    | "-h" `elem` args || "--help" `elem` args = printHelpMsg
    | otherwise = do 
    config <- parseConfig args

    case config of 
        Left err -> logErr . show $ err
        Right _ -> return ()

-- | Config object from command line arguments
data Config = Config {
    file :: String,     -- ^ file to run
    interactive :: Bool -- ^ if in an interactive session (maybe?)
}

-- | Possible errors por the command line
data CLIError = 
    NotEnoughArgs |            -- ^ Called when there's not enough arguments while parsing configs for the cli tool
    FileDoesNotExists String | -- ^ Called when the provided file argument does not exists 
    InvalidFileFormat          -- ^ The filename doesn't ends with .tac
    deriving(Eq)    

-- | Parse a config object from the provided command line arguments
parseConfig :: [String] -> IO (Either CLIError Config)
parseConfig args 
    | null args = return $ Left NotEnoughArgs -- check that at the least, the file argument is provided\
    | otherwise = do

        -- Parse args
        let (fileName:rest) = args

        -- Check file existence 
        fileExists <- doesFileExist fileName

        let inter = "-i" `elem` args || "--interactive" `elem` args

        unless (null rest) $ do
            logWarn "Too many arguments, ignoring the rest"

        -- set up result
        let res 
                | not fileExists = Left (FileDoesNotExists fileName)
                | not $ ".tac" `isSuffixOf` fileName = Left InvalidFileFormat
                | otherwise = Right $ Config{interactive = inter, file=fileName}

        return res

printHelpMsg :: IO ()
printHelpMsg = do
    putStrLn "\tTAC Code Interpreter (taci). Provide a file with extension '.tac' to run it"
    putStrLn "\tAvailable commnads: "
    putStrLn "Still wip 🤪"

-- < Utility functions > -----------------------------------
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

instance Show CLIError where
    show NotEnoughArgs         = "Not enough arguments, you should provide at the least the file to run"
    show (FileDoesNotExists s) = "The provided file '" ++ s ++ "' does not exists"
    show InvalidFileFormat     = "Invalid file format, should end with '.tac'"




