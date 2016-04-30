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

    Properties {
        condition: project.enableInternalTesting
        cpp.defines: [
            'SCT_BUILD_INTERNAL_API',
            'SCT_INTERNAL_LIB'
        ].concat(outer)
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Sources                                                                                   //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    files: [
        "core/exception/exception.cpp",
        "core/exception/exception.hpp",
        "core/exception/exceptionhandler.hpp",
        "core/exception/exceptionhandler.inl",
        "core/exception/nullpointerexception.cpp",
        "core/exception/nullpointerexception.hpp",
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
            "Core/Exception/Exception",
            "Core/Exception/ExceptionHandler",
            "Core/Exception/NullPointerException",
            "Control",
            "Padding",
            "global.hpp"
        ]
    }

    Group {
        name: "[API] Internal"
        fileTags: ['stoiridh.controls.templates.api.internal']
        overrideTags: false
        prefix: 'api/internal/'
        files: [
            "style/utility/stylefactoryhelper.cpp",
            "style/utility/stylefactoryhelper.hpp",
            "style/abstractstyledispatcher.cpp",
            "style/abstractstyledispatcher.hpp",
            "style/style.cpp",
            "style/style.hpp",
            "style/styledispatcher.cpp",
            "style/styledispatcher.hpp",
            "style/stylefactory.cpp",
            "style/stylefactory.hpp",
            "style/stylefactory.inl",
            "style/stylepropertychanges.cpp",
            "style/stylepropertychanges.hpp",
            "style/stylepropertychangesparser.cpp",
            "style/stylepropertychangesparser.hpp",
            "style/stylepropertyexpression.cpp",
            "style/stylepropertyexpression.hpp",
            "style/stylestate.cpp",
            "style/stylestate.hpp",
            "style/stylestatecontroller.cpp",
            "style/stylestatecontroller.hpp",
            "style/stylestateoperation.cpp",
            "style/stylestateoperation.hpp",
            "abstractcontrol.hpp",
            "global.hpp",
        ]
    }

    Group {
        name: "[API] Private"
        fileTags: ['stoiridh.controls.templates.api.private']
        overrideTags: false
        prefix: 'api/private/'
        files: [
            "bootstrap/qmlextensionplugin.cpp",
            "bootstrap/qmlextensionplugin_p.hpp",
            "style/style_p.hpp",
            "style/stylepropertychanges_p.hpp",
            "style/stylestate_p.hpp",
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

        cpp.includePaths: {
            var paths = [];
            paths.push(FileInfo.joinPaths(product.buildDirectory, 'include'));

            if (project.enableInternalTesting) {
                paths.push('.');
            }

            return paths;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Rules                                                                                     //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    FileTagger {
        patterns: ["*.inl"]
        fileTags: ["hpp"]
    }

    Rule {
        inputs: [
            'hpp',
            'stoiridh.controls.templates.api.internal',
            'stoiridh.controls.templates.api.private',
            'stoiridh.controls.templates.api.public'
        ]

        outputFileTags: ['stoiridh.controls.templates.api']
        outputArtifacts: {
            var fileTags = input.fileTags;

            var internalFileTag = 'stoiridh.controls.templates.api.internal';
            var privateFileTag = 'stoiridh.controls.templates.api.private';
            var publicFileTag = 'stoiridh.controls.templates.api.public';

            if (fileTags.contains('unmocable') || fileTags.contains('cpp'))
                return [];

            if (!project.enableInternalTesting && fileTags.contains(internalFileTag))
                return [];

            var artefacts = [];

            var destinationPath = 'include/StoiridhControlsTemplates';
            var relativeFilePath = FileInfo.relativePath(product.sourceDirectory, input.filePath);

            if (fileTags.contains(publicFileTag)) {
                relativeFilePath = relativeFilePath.replace('api/public/', '');
                artefacts.push({
                    filePath: FileInfo.joinPaths(destinationPath, relativeFilePath),
                    fileTags: ['stoiridh.controls.templates.api']
                });
            } else if (fileTags.contains(internalFileTag)) {
                relativeFilePath = relativeFilePath.replace('api/internal/', '');
                artifacts.push({
                    filePath: FileInfo.joinPaths(destinationPath, 'Internal', relativeFilePath),
                    fileTags: ['stoiridh.controls.templates.api']
                });
            } else if (fileTags.contains(privateFileTag)) {
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
