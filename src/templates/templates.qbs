////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//            Copyright (C) 2016 William McKIE                                                    //
//                                                                                                //
//            This program is free software: you can redistribute it and/or modify                //
//            it under the terms of the GNU General Public License as published by                //
//            the Free Software Foundation, either version 3 of the License, or                   //
//            (at your option) any later version.                                                 //
//                                                                                                //
//            This program is distributed in the hope that it will be useful,                     //
//            but WITHOUT ANY WARRANTY; without even the implied warranty of                      //
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       //
//            GNU General Public License for more details.                                        //
//                                                                                                //
//            You should have received a copy of the GNU General Public License                   //
//            along with this program.  If not, see <http://www.gnu.org/licenses/>.               //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
import qbs 1.0
import qbs.File
import qbs.FileInfo
import Stoiridh.QtQuick

QtQuick.DynamicLibrary {
    name: "Stoiridh.Controls.Templates"
    targetName: "StoiridhControlsTemplates"
    type: ['stoiridh.controls.templates.hpp'].concat(base)
    installFileTagsFilter: ['dynamiclibrary']

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Configuration                                                                             //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    cpp.defines: ['STOIRIDH_CONTROLS_TEMPLATES_LIB'].concat(base)
    cpp.includePaths: [FileInfo.joinPaths(product.buildDirectory, 'include')].concat(base)

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Sources                                                                                   //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    files: [
        "control.cpp",
        "control.hpp",
        "global.hpp",
        "padding.cpp",
        "padding.hpp",
    ]
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Exports                                                                                   //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Export {
        Depends { name: 'cpp' }

        cpp.includePaths: [].concat(FileInfo.joinPaths(product.buildDirectory, 'include'))
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Rules                                                                                     //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Rule {
        inputs: ['hpp']

        Artifact {
            fileTags: ['stoiridh.controls.templates.hpp']
            filePath: {
                var relativeFilePath = FileInfo.relativePath(product.sourceDirectory,
                                                             input.filePath);

                return FileInfo.joinPaths('include/StoiridhControlsTemplates', relativeFilePath);
            }
        }

        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = 'copying ' + input.fileName;
            cmd.highlight = 'filegen';
            cmd.silent = true;
            cmd.sourceCode = function() {
                File.copy(input.filePath, output.filePath);
            };
            return cmd;
        }
    }
}
