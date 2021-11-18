{-
    Main application implementation
-}
{-# OPTIONS_GHC -Wall #-}
module Taci.TacRunner where

-- Internal imports
import qualified Utils as U

-- Haskell imports
import qualified Control.Monad.RWS as RWS
import qualified Control.Monad as M

-- External imports
import qualified TACTypes.TAC as T


-- >> Data Definitions
-- | Current state
data RunnerState = State{} deriving(Eq, Show)

-- | Runner monad to use for stateful computations
type RunnerMonad = RWS.RWST () () RunnerState IO

-- >> Main Function 
runTac :: T.TACProgram -> IO RunnerState
runTac program = do
    (resultState, _) <- RWS.execRWST (runTac' program) () newRunnerState
    return resultState

-- < State functions > ---------------------------------

-- | Create a new runner state in initial state
newRunnerState :: RunnerState
newRunnerState = State

-- < Execution functionality > -------------------------

-- | Run a tac program inside the state monad
runTac' :: T.TACProgram -> RunnerMonad ()
runTac' (T.TACProgram tacCodes) = M.forM_ tacCodes runTacInst


-- | Function to call over each tac operation 
runTacInst :: T.TACCode  -> RunnerMonad ()
runTacInst code = do                    -- Default implementation for simple instructions, if you need 
    state <- RWS.get                    -- more control, feel free to add variations to this function
    RWS.put (runTacInst' code state)

-- | Functional version for easy instructions
runTacInst' :: T.TACCode -> RunnerState -> RunnerState
runTacInst' code state = undefined