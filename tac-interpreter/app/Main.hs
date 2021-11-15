module Main where

import Lib(taci)

import System.Environment

main :: IO ()
main = getArgs >>= taci
