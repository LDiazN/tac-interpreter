{-
    This file implements the cli tool and the main function for this app
-}
{-# OPTIONS_GHC -Wall #-}
module Lib
    ( taci
    ) where

-- Haskell imports
import System.IO(readFile)
import System.Directory ( doesFileExist )
import Data.List(isSuffixOf)
import Control.Monad(unless)

-- Local imports 
import qualified Utils as U
import qualified Taci.TacRunner as TR

-- External imports
import qualified TACTypes.TAC as T


-- Main function. Execute app with a given set of command line arguments, including the command name
taci :: [String] -> IO()
taci args 
    | "-h" `elem` args || "--help" `elem` args = printHelpMsg
    | otherwise = do 

    -- Try to parse config from arguments
    config <- parseConfig args

    case config of 
        Left err -> U.logErr . show $ err
        Right Config {file=_file, interactive=_interactive} -> do 
            -- Read file to string
            programStr <- readFile _file

            -- Try to parse it 
            let program = T.parse programStr
            
            -- Run tac program 
            resultState <- TR.runTac program

            -- Print result state
            print resultState
            return ()


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
            U.logWarn "Too many arguments, ignoring the rest"

        -- set up result
        let res 
                | not fileExists = Left (FileDoesNotExists fileName)
                | not $ ".tac" `isSuffixOf` fileName = Left InvalidFileFormat
                | otherwise = Right $ Config{interactive = inter, file=fileName}

        return res

-- | Help message to print when the user requests the flag --help
printHelpMsg :: IO ()
printHelpMsg = do
    putStrLn "\tTAC Code Interpreter (taci). Provide a file with extension '.tac' to run it"
    putStrLn "\tAvailable commnads: "
    putStrLn "Still wip 🤪"


instance Show CLIError where
    show NotEnoughArgs         = "Not enough arguments, you should provide at the least the file to run"
    show (FileDoesNotExists s) = "The provided file '" ++ s ++ "' does not exists"
    show InvalidFileFormat     = "Invalid file format, should end with '.tac'"




