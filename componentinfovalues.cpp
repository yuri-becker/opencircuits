/*
 *  componentinfovalues.cpp: Implementation of componentinfovalues.h
 *
 * Copyright (C) 2015-2016 Yuri Becker <hi@yuri.li>
 *
 * This file is part of OpenCircuits.
 *
 * OpenCircuits is free software: you can redistribute it and/or modify it under the terms
 * of the GNU Lesser General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * OpenCircuits is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU  Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with
 * OpenCircuits. If not, see <http://www.gnu.org/licenses/>.
 * */

#include "componentinfovalues.h"

#include "Components/abstractblock.h"

ComponentInfo ComponentInfoValues::getComponentInfo(int blockType)
{
    if(blockType == AbstractBlock::LED) return ledInfo();
    else if(blockType == AbstractBlock::SOURCE) return sourceInfo();
    else if(blockType == AbstractBlock::ANDGATE) return andgateInfo();
    else if(blockType == AbstractBlock::ORGATE) return orgateInfo();
    else if(blockType == AbstractBlock::NOTGATE) return notgateInfo();
    else if(blockType == AbstractBlock::NANDGATE) return nandgateInfo();
    else if(blockType == AbstractBlock::NORGATE) return norgateInfo();
    else if(blockType == AbstractBlock::XORGATE) return xorgateInfo();
    else if(blockType == AbstractBlock::XNORGATE) return xnorgateInfo();
    else if(blockType == AbstractBlock::LABEL) return labelInfo();
    else if(blockType == AbstractBlock::SPLITTER) return splitterInfo();
    else if(blockType == AbstractBlock::SQUAREFUNCTIONGENERATOR) return squareFunctionGeneratorInfo();
    else if(blockType == AbstractBlock::PUSHBUTTON) return pushButtonInfo();
    else if(blockType == AbstractBlock::SWITCH) return switchInfo();
    else if(blockType == AbstractBlock::SRNORLATCH) return srNorLatchInfo();
    else if(blockType == AbstractBlock::TFLIPFLOP) return tFlipFlopInfo();
    else if(blockType == AbstractBlock::JKFLIPFLOP) return jkFlipFlopInfo();
    else if(blockType == AbstractBlock::MULTIPLEXER) return multiplexerInfo();
    else if(blockType == AbstractBlock::DEMULTIPLEXER) return demultiplexerInfo();
    else if(blockType == AbstractBlock::GATEDSRNORLATCH) return gatedSrNorLatchInfo();
    else if(blockType == AbstractBlock::GATEDJKFLIPFLOP) return gatedJkFlipFlopInfo();
    else return ComponentInfo(-1, "", "https://github.com/CubicVoxel/opencircuits/wiki/Components");
}

ComponentInfo ComponentInfoValues::ledInfo()
{
    return ComponentInfo(
                AbstractBlock::LED,
                tr("LED"),
               "https://github.com/CubicVoxel/opencircuits/wiki/Components#led"
                );
}

ComponentInfo ComponentInfoValues::sourceInfo()
{
    return ComponentInfo(
                AbstractBlock::SOURCE,
                tr("Source"),
               "https://github.com/CubicVoxel/opencircuits/wiki/Components#source"
                );
}

ComponentInfo ComponentInfoValues::andgateInfo()
{
    return ComponentInfo(
                AbstractBlock::ANDGATE,
                tr("AND Gate"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#and-gate-"
                );
}

ComponentInfo ComponentInfoValues::orgateInfo()
{
    return ComponentInfo(
                AbstractBlock::ORGATE,
                tr("OR Gate"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#or-gate-1"
                );
}

ComponentInfo ComponentInfoValues::notgateInfo()
{
    return ComponentInfo(
                AbstractBlock::NOTGATE,
                tr("NOT Gate"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#not-gate-1"
                );
}

ComponentInfo ComponentInfoValues::nandgateInfo()
{
    return ComponentInfo(
                AbstractBlock::NANDGATE,
                tr("NAND Gate"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#nand-gate-"
                );
}

ComponentInfo ComponentInfoValues::norgateInfo()
{
    return ComponentInfo(
                AbstractBlock::NORGATE,
                tr("NOR Gate"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#nor-gate-1"
                );
}

ComponentInfo ComponentInfoValues::xorgateInfo()
{
    return ComponentInfo(
            AbstractBlock::XORGATE,
            tr("XOR Gate"),
            "https://github.com/CubicVoxel/opencircuits/wiki/Components#xor-gate-1"
            );
}

ComponentInfo ComponentInfoValues::xnorgateInfo()
{
    return ComponentInfo(
                AbstractBlock::XNORGATE,
                tr("XNOR Gate"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#xnor-gate-1"
                );
}

ComponentInfo ComponentInfoValues::labelInfo()
{
    return ComponentInfo(
                AbstractBlock::LABEL,
                tr("Label"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#label"
                );
}

ComponentInfo ComponentInfoValues::splitterInfo()
{
    return ComponentInfo(
                AbstractBlock::SPLITTER,
                tr("Splitter"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components"
                );
}

ComponentInfo ComponentInfoValues::squareFunctionGeneratorInfo()
{
    return ComponentInfo(
                AbstractBlock::SQUAREFUNCTIONGENERATOR,
                tr("Square Function Generator"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#square-function-generator"
                );
}

ComponentInfo ComponentInfoValues::pushButtonInfo()
{
    return ComponentInfo(
                AbstractBlock::PUSHBUTTON,
                tr("Push-Button"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#push-button"
                );
}

ComponentInfo ComponentInfoValues::switchInfo()
{
    return ComponentInfo(
                AbstractBlock::SWITCH,
                tr("Switch"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#switch"
                );
}

ComponentInfo ComponentInfoValues::srNorLatchInfo()
{
    return ComponentInfo(
                AbstractBlock::SRNORLATCH,
                tr("SR NOR Latch"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#sr-nor-latch"
                );
}

ComponentInfo ComponentInfoValues::tFlipFlopInfo()
{
    return ComponentInfo(
                AbstractBlock::TFLIPFLOP,
                tr("T flip-flop"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#t-flip-flop"
                );
}

ComponentInfo ComponentInfoValues::jkFlipFlopInfo()
{
    return ComponentInfo(
                AbstractBlock::JKFLIPFLOP,
                tr("JK flip-flop"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#jk-flip-flop"
                );
}

ComponentInfo ComponentInfoValues::multiplexerInfo()
{
    return ComponentInfo(
                AbstractBlock::MULTIPLEXER,
                tr("Multiplexer"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#multiplexer"
                );
}

ComponentInfo ComponentInfoValues::demultiplexerInfo()
{
    return ComponentInfo(
                AbstractBlock::DEMULTIPLEXER,
                tr("Demultiplexer"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#demultiplexer"
                );
}

ComponentInfo ComponentInfoValues::gatedSrNorLatchInfo()
{
    return ComponentInfo(
                AbstractBlock::GATEDSRNORLATCH,
                tr("Gated SR NOR latch"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#gated-sr-nor-latch"
                );
}

ComponentInfo ComponentInfoValues::gatedJkFlipFlopInfo()
{
    return ComponentInfo(
                AbstractBlock::GATEDJKFLIPFLOP,
                tr("Gated JK flip-flop"),
                "https://github.com/CubicVoxel/opencircuits/wiki/Components#gated-jk-flip-flop"
                );
}

ComponentInfoValues::ComponentInfoValues()
{

}



