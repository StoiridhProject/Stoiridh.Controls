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
    type: ['stoiridh.controls.templates.api'].concat(base)
    installFileTagsFilter: ['dynamiclibrary']

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Dependencies                                                                              //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Depends {
        name: 'Qt'
        submodules: [
            'core-private',
            'gui-private',
            'qml-private',
            'quick-private'
        ]
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Configuration                                                                             //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    cpp.defines: [
        'STOIRIDH_CONTROLS_TEMPLATES_LIB',
        'QT_NO_CAST_FROM_ASCII',
        'QT_NO_CAST_TO_ASCII'
    ].concat(base)

    cpp.includePaths: [
        FileInfo.joinPaths(product.buildDirectory, 'include'),
        product.sourceDirectory,
    ].concat(base)

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

    Group {
        name: "[API] Public"
        fileTags: ['stoiridh.controls.templates.api.public']
        overrideTags: true
        prefix: 'api/public/'
        files: [
            "Control",
            "Padding",
        ]
    }

    Group {
        name: "[API] Private"
        fileTags: ['stoiridh.controls.templates.api.private']
        overrideTags: false
        prefix: 'api/private/'
        files: [
            "control_p.hpp",
        ]
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Exports                                                                                   //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Export {
        Depends { name: 'cpp' }

        cpp.defines: [
            'QT_NO_CAST_FROM_ASCII',
            'QT_NO_CAST_TO_ASCII'
        ]

        cpp.includePaths: [].concat(FileInfo.joinPaths(product.buildDirectory, 'include'))
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Rules                                                                                     //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Rule {
        inputs: [
            'hpp',
            'stoiridh.controls.templates.api.public',
            'stoiridh.controls.templates.api.private'
        ]

        outputFileTags: ['stoiridh.controls.templates.api']
        outputArtifacts: {
            var fileTags = input.fileTags;

            if (fileTags.contains('unmocable'))
                return [];

            var artefacts = [];

            var destinationPath = 'include/StoiridhControlsTemplates';
            var relativeFilePath = FileInfo.relativePath(product.sourceDirectory, input.filePath);

            if (fileTags.contains('stoiridh.controls.templates.api.public')) {
                relativeFilePath = relativeFilePath.replace('api/public/', '');
                artefacts.push({
                    filePath: FileInfo.joinPaths(destinationPath, relativeFilePath),
                    fileTags: ['stoiridh.controls.templates.api']
                });
            } else if (fileTags.contains('stoiridh.controls.templates.api.private')) {
                relativeFilePath = relativeFilePath.replace('api/private/', '');
                artefacts.push({
                    filePath: FileInfo.joinPaths(destinationPath, 'Private', relativeFilePath),
                    fileTags: ['stoiridh.controls.templates.api']
                });
            } else if (fileTags.contains('hpp')) {
                artefacts.push({
                    filePath: FileInfo.joinPaths(destinationPath, 'Public', relativeFilePath),
                    fileTags: ['stoiridh.controls.templates.api']
                });
            }

            return artefacts;
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
